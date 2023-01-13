
from rest_framework import status
from ..azureVoice.voice_generation import generate_voice,VOICE_OPTIONS_DISPLAY,validate_options

from rest_framework.decorators import authentication_classes,permission_classes,api_view
from rest_framework.permissions import IsAuthenticated
from rest_framework.views import APIView, Response

from first import serializers
from ..banned_word_and_contents import SensitiveFilter
from ..azureVoice.azureService import SpeechSynthesizer as SS

from ..models import Follow, UserPost, Like, UserImage, UserVoice

from ..custom_authentication import AuthingIDAuthentication
from ..ip_adress import ipAddress

from ..pagination.custom import CustomPagination

@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def get_voice_options(request):
    return Response(VOICE_OPTIONS_DISPLAY)

class UserPostView(APIView):
    authentication_classes = (AuthingIDAuthentication,)
    permission_classes = (IsAuthenticated,)

    def post(self, request, reply_id=None):
        """
        用户发布文章
        """
        if request.user.is_banned and not request.user.is_admin:
            return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
        # 自动屏蔽
        Filter = SensitiveFilter()
        if 'post' not in request.data:
            return Response({'status': 'error', 'message': 'post字段缺失'}, status=status.HTTP_400_BAD_REQUEST)
        request.data['post'] = Filter.replaceSensitiveWord(request.data['post'])
        if 'title' in request.data:
            request.data['title'] = Filter.replaceSensitiveWord(request.data['title'])
        serialize_data = request.data
        serialize_data['ip_loc'] = ipAddress.get_ip_loc(request)[0]

        serializer = serializers.UserPostSerializer(data=serialize_data)
        if serializer.is_valid():
            reply_to: UserPost
            #回复贴,没有图片、语音
            if reply_id:
                try:
                    reply_to = UserPost.objects.get(id=reply_id)
                except UserPost.DoesNotExist:
                    return Response({"detail": "回复的主题帖不存在"}, status=status.HTTP_404_NOT_FOUND)
                serializer.save(user=request.user, reply_to=reply_to)
            #主题帖,需要图片、语音
            else:
                # 处理主题帖使用的图片
                images_serializer = serializers.CreatePostImageSerializer(data=request.data,
                                                                          context={'request': request})
                # 处理主题帖需要的语音
                voice_enable_serializer = serializers.CreatePostEnableReadSerializer(data=request.data)
                post_id = -1
                if not voice_enable_serializer.is_valid():
                    return Response(voice_enable_serializer.errors, status=status.HTTP_400_BAD_REQUEST)
                if not images_serializer.is_valid():
                    return Response(images_serializer.errors, status=status.HTTP_400_BAD_REQUEST)

                #处理语音选项
                voice_option_serializer = None
                if voice_enable_serializer.validated_data['enableVoice']:
                    voice_option_serializer = serializers.CreatePostReadOptionSerializer(data=request.data)
                    if not voice_option_serializer.is_valid():
                        return Response(voice_option_serializer.errors, status=status.HTTP_400_BAD_REQUEST)
                    if not validate_options(voice_option_serializer.validated_data['speakerId'],voice_option_serializer.validated_data['styleId']):
                        return Response({"detail":"无效的讲话人ID与说话风格ID"}, status=status.HTTP_400_BAD_REQUEST)

                serializer.save(user=request.user)
                post_id = serializer.data['id']
                for image_id in images_serializer.validated_data['images']:
                    image = UserImage.objects.get(id=image_id)
                    image.post_id = post_id
                    image.save()

                if voice_enable_serializer.validated_data['enableVoice']:

                    url = generate_voice(content=request.data['post'],speaker_id=voice_option_serializer.validated_data['speakerId'],style_id=voice_option_serializer.validated_data['styleId'])

                    voice = UserVoice(creator_id=request.user.id, voice_url=url, post_id=post_id)
                    voice.save()

            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    def get(self, request, id=None):
        """
        用户浏览文章
        params in restful api:
            id: 帖子id
        params in query parameters:
            post_id: 帖子id （可选，只看特定帖，在使用restful格式时被覆盖）
            user_id: 用户id （可选，只看特定用户，在只看特定帖子时被覆盖）
            only_see_following: 只看关注的人的帖子（可选，不声明时默认为None，查看所有帖，在只看特定帖或特定用户时被覆盖）
            page: 页码（可选，默认为1，在只看特定帖子时被覆盖）
        """
        if request.user.is_banned and not request.user.is_admin:
            return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)

        page = request.query_params.get('page', '1')
        page = int(page)

        post_id: str
        if id:  # restful格式
            post_id = str(id)
        else:  # query parameters格式
            post_id = request.query_params.get('post_id', None)
        only_see_following = request.query_params.get('only_see_following', False)
        user_id = request.query_params.get('user_id', None)
        post: UserPost
        if post_id:  # 查看某一篇文章
            try:
                post = UserPost.objects.get(id=post_id)
                if post.user != request.user:
                    post.visited_count += 1
                post.save()
            except UserPost.DoesNotExist:
                return Response({"detail": "该帖子不存在"}, status=status.HTTP_404_NOT_FOUND)

            counts = {
                'like_count': Like.objects.filter(post_id=post_id).count(),
                'reply_count': UserPost.objects.exclude(reply_to=None).filter(reply_to=post_id).count(),
                'is_liked': Like.objects.filter(user=request.user, post=post).exists()
            }
            return Response({**serializers.GetPostSerializer(post).data, **counts}, status=status.HTTP_200_OK)
        if user_id:  # 查看某一个用户的帖子
            show_all = request.query_params.get('all', 'false')
            if show_all == 'true':
                return Response(serializers.GetPostSerializer(
                    UserPost.objects.filter(user=user_id), many=True).data)
            return Response(serializers.GetPostSerializer(
                CustomPagination.paginate_queryset(page,UserPost.objects.filter(user=user_id, reply_to=None).order_by('-id')), many=True).data)
        if only_see_following == 'true':  # 查看关注的人的所有文章
            followings = Follow.objects.filter(follower_id=request.user).values('user_id')
            followings = list(map(lambda x: x['user_id'], list(followings)))

            posts = serializers.GetPostSerializer(CustomPagination.paginate_queryset(page,
                UserPost.objects.filter(user__in=followings, reply_to=None).order_by('-id')),
                many=True
            ).data


            for i in range(len(posts)):
                posts[i]['like_count'] = Like.objects.filter(post_id=posts[i]['id']).count()
                posts[i]['reply_count'] = UserPost.objects.exclude(reply_to=None).filter(
                    reply_to=posts[i]['id']).count()
                posts[i]['is_liked'] = Like.objects.filter(user_id=request.user.id, post_id=posts[i]['id']).exists()

            return Response(posts)
        else:  # 查看所有文章

            posts = serializers.GetPostSerializer(CustomPagination.paginate_queryset(
                page,
                UserPost.objects.filter(reply_to=None).order_by('-id')),
                many=True
            ).data
            for i in range(len(posts)):
                posts[i]['like_count'] = Like.objects.filter(post_id=posts[i]['id']).count()
                posts[i]['reply_count'] = UserPost.objects.exclude(reply_to=None).filter(
                    reply_to=posts[i]['id']).count()
                posts[i]['is_liked'] = Like.objects.filter(user_id=request.user.id, post_id=posts[i]['id']).exists()

            return Response(posts)

    def delete(self, request, id=None):
        """
        用户删除文章
        params in query parameters:
            post_id: 帖子id
        """
        if request.user.is_banned and not request.user.is_admin:
            return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
        post_id = id
        try:
            post = UserPost.objects.get(id=post_id)
            if request.user.is_admin == False and post.user.id != request.user.id:
                return Response({"detail": "没有权限"}, status=status.HTTP_403_FORBIDDEN)
        except UserPost.DoesNotExist:
            return Response({"detail": "该帖子不存在"}, status=status.HTTP_404_NOT_FOUND)
        post.delete()
        return Response({'status': 'success'})

