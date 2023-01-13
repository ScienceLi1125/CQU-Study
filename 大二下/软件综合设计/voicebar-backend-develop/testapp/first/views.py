import base64

from os.path import dirname, abspath
import os

from django.db import IntegrityError
from django.db.models import Window, F
from django.http import Http404
from rest_framework import status
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from rest_framework.permissions import IsAuthenticated
from rest_framework.views import APIView, Response

from first import serializers
from .banned_word_and_contents import SensitiveFilter
from .azureVoice.azureService import SpeechSynthesizer as SS
from .models import User, Follow, UserPost, Like, UserImage, UserVoice
from .serializers import UserProfileSerializer, UserProfileListSerializer, \
    UpdateAvatarSerializer, UploadPostImageSerializer, CreatePostImageSerializer, GetPostSerializer
from .tencent_cos.api import upload_file_cos, COSFileType

from .ip_adress import ipAddress

from .authing.registerView import register_by_email, register_by_phone_code
from .face.face import face

from .views_archived.countView import user_liked_count,user_comments_count,user_follower_count,user_following_count,\
                                    user_main_posts_count, post_liked_count, post_comment_count, post_read_count
from .views_archived.searchView import search_post_title, search_post_content, search_post_full
from .views_archived.ipView import get_ip_loc
from .views_archived.likeView import LikeView, user_like_list, is_post_liked
from .views_archived.followView import FollowView, get_user_followers, get_self_followers, get_user_followings,\
                                        get_user_followers, get_self_followings, get_is_following
from .views_archived.postView import UserPostView, get_voice_options
from .views_archived.faceView import face_to_mp3_post, create_post_with_result_record
from .views_archived.adminView import ban_user, unban_user, delete_user
from .views_archived import statisticView

from .pagination.custom import CustomPagination

# Create your views here.


from .custom_authentication import AuthingIDAuthentication


class SelfProfileView(APIView):
    """
    用户查看和修改个人资料
    """
    authentication_classes = (AuthingIDAuthentication,)
    permission_classes = (IsAuthenticated,)

    def get(self, request):
        """
        返回个人资料
        """
        if request.user.is_banned and not request.user.is_admin:
            return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
        
        #同时返回粉丝数、关注数
        self_follower_count = Follow.objects.filter(user_id=request.user.id).count()
        self_following_count = Follow.objects.filter(follower_id=request.user.id).count()
        result = UserProfileSerializer(request.user).data
        result['follower_count'] = self_follower_count
        result['following_count'] = self_following_count

        return Response(result)

    def patch(self, request):
        """
        更改个人资料
        """

        if request.user.is_banned and not request.user.is_admin:
            return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)

        Filter = SensitiveFilter()
        # 自动屏蔽
        if 'motto' in request.data:
            motto = Filter.replaceSensitiveWord(request.data['motto'])
            request.data['motto'] = motto
        # 判断是否含敏感词汇在昵称中,并返回提示
        if 'nickname' in request.data:
            name = Filter.replaceSensitiveWord(request.data['nickname'])
            if name != request.data['nickname']:
                request.data['nickname'] = name
                serializer = UserProfileSerializer(User.objects.get(id=request.user.id), data=request.data)
                if serializer.is_valid():
                    serializer.save()
                return Response({'status': 'error', 'message': '昵称违规，含敏感词汇', "new_name": name},
                                status=status.HTTP_400_BAD_REQUEST)

        serializer = UserProfileSerializer(User.objects.get(id=request.user.id), data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response({'status': 'success'})
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


@api_view(['PATCH'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def update_self_avatar(request):
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    serializer = UpdateAvatarSerializer(data=request.data)
    if not serializer.is_valid():
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
    new_avatar = serializer.validated_data['avatar']
    filename = new_avatar.name
    file_ext = ""
    if len(filename.split('.')) >= 2:
        file_ext = filename.split('.')[-1]
    new_avatar_url = upload_file_cos(file_type=COSFileType.AVATAR, file_content=new_avatar.read(),
                                     file_extension=file_ext, content_type=new_avatar.content_type)
    user: User = User.objects.get(id=request.user.id)
    user.avatar_url = new_avatar_url
    user.save()
    return Response({'status': 'success'})


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def users_profile_list(request):
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    ITEM_PER_PAGE = 10
    page = request.query_params.get('page', '1')
    page = int(page)
    # 根据page算出起点与终点
    start_offset = (page - 1) * ITEM_PER_PAGE
    # https://docs.djangoproject.com/zh-hans/4.1/topics/db/queries/
    users = User.objects.all()[start_offset:start_offset + ITEM_PER_PAGE]
    serializer = UserProfileListSerializer(users, many=True)
    return Response(serializer.data)




@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def users_profile_detail(request, id):
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    user: User
    try:
        user = User.objects.get(id=id)
    except User.DoesNotExist:
        return Response({"detail": "Not Found"}, status=status.HTTP_404_NOT_FOUND)
    serializer = UserProfileSerializer(user)
    #同时返回粉丝数、关注数
    follower_count = Follow.objects.filter(user_id=user.id).count()
    following_count = Follow.objects.filter(follower_id=user.id).count()
    result = serializer.data
    result['follower_count'] = follower_count
    result['following_count'] = following_count
    return Response(result)





class CommentUserView(APIView):
    authentication_classes = (AuthingIDAuthentication,)
    permission_classes = (IsAuthenticated,)

    def get(self, request, user_id):
        """
        返回用户的所有回复帖
        params in query parameters:
            page: 页码（可选，默认为1）
        """
        if request.user.is_banned and not request.user.is_admin:
            return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)

        page_serializer = serializers.GetParamsPageSerializer(data=request.query_params)
        if not page_serializer.is_valid():
            return Response(page_serializer.errors,status=status.HTTP_400_BAD_REQUEST)
        page = page_serializer.validated_data['page']


        return Response(serializers.UserPostSerializer(CustomPagination.paginate_queryset(
            page,
            UserPost.objects.exclude(reply_to=None).filter(user=user_id).order_by('-id')),
            many=True
        ).data)


class CommentPostView(APIView):
    authentication_classes = (AuthingIDAuthentication,)
    permission_classes = (IsAuthenticated,)

    def get(self, request, post_id):
        """
        返回帖子的回复帖列表
        params in query parameters:
            page: 页码（可选，默认为1）
        """
        if request.user.is_banned and not request.user.is_admin:
            return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)

        page_serializer = serializers.GetParamsPageSerializer(data=request.query_params)
        if not page_serializer.is_valid():
            return Response(page_serializer.errors,status=status.HTTP_400_BAD_REQUEST)
        page = page_serializer.validated_data['page']

        total_comments = UserPost.objects.exclude(reply_to=None).filter(reply_to=post_id).count()

        result = serializers.UserPostSerializer(
            UserPost.objects.exclude(reply_to=None).filter(reply_to=post_id),
            many=True
        ).data

        #添加楼数
        it = iter(range(1, total_comments + 1))
        for i in result:
            i.update({'index': next(it)})


        return Response(CustomPagination.paginate_queryset(page,result))




@api_view(['POST'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def upload_image(request):
    """
    用户上传文件
    用于: 文章图片
    """
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    serializer = UploadPostImageSerializer(data=request.data)
    if not serializer.is_valid():
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
    result: int
    image = serializer.validated_data['image']
    filename = image.name
    file_ext = ""
    if len(filename.split('.')) >= 2:
        file_ext = filename.split('.')[-1]
    image_url = upload_file_cos(file_type=COSFileType.ARTICLE_IMAGE, file_content=image.read(), file_extension=file_ext,
                                content_type=image.content_type)
    new_image = UserImage(creator_id=request.user.id, image_url=image_url)
    new_image.save()
    result = new_image.id
    return Response({'id': result})

@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def admin_get_all(request):
    if request.user.is_admin:
        ITEM_PER_PAGE = 10
        page = request.query_params.get('page', '1')
        page = int(page)
        # 根据page算出起点与终点
        start_offset = (page - 1) * ITEM_PER_PAGE
        # https://docs.djangoproject.com/zh-hans/4.1/topics/db/queries/
        users = User.objects.filter(is_admin=0).all()[start_offset:start_offset + ITEM_PER_PAGE]
        serializer = UserProfileListSerializer(users, many=True)
        return Response(serializer.data)

