from django.db import IntegrityError
from rest_framework import status
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from rest_framework.permissions import IsAuthenticated
from rest_framework.views import Response, APIView

from first import serializers
from ..models import User, Follow
from ..custom_authentication import AuthingIDAuthentication
from ..pagination.custom import CustomPagination



class FollowView(APIView):
    authentication_classes = (AuthingIDAuthentication,)
    permission_classes = (IsAuthenticated,)

    def post(self, request, format=None):
        """
        用户关注用户
        只能由自己发起关注
        """
        if request.user.is_banned and not request.user.is_admin:
            return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
        serializer = serializers.FollowSerializer(data=request.data)
        if serializer.is_valid():
            if str(request.data.get('user')) == str(request.user.id):
                return Response({'detail': '不能关注自己'}, status=status.HTTP_400_BAD_REQUEST)
            try:
                serializer.save(follower=request.user)

            except IntegrityError:
                return Response("{''detail':'不能重复关注'}", status=status.HTTP_400_BAD_REQUEST)
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    def get(self, request):
        """
        返回用户关注的用户列表或粉丝列表
        params in request body:
            user: 被关注用户id
            follower: 发起关注用户id
            following: 默认返回粉丝列表，为'true'时返回关注列表
            page: 页码（可选，默认为1）
        """
        if request.user.is_banned and not request.user.is_admin:
            return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
        ITEM_PER_PAGE = 10
        page = request.query_params.get('page', '1')
        page = int(page)
        start_offset = (page - 1) * ITEM_PER_PAGE

        following = request.query_params.get('following', 'false')
        if following == 'true':  # 关注列表
            return Response(serializers.FollowSerializer(
                Follow.objects.filter(follower=request.user.id)[start_offset:start_offset + ITEM_PER_PAGE],
                many=True
            ).data)
        else:  # 粉丝列表
            return Response(serializers.FollowSerializer(
                Follow.objects.filter(user_id=request.user.id)[start_offset:start_offset + ITEM_PER_PAGE],
                many=True
            ).data)

    def delete(self, request):
        """
        取消关注
        用户只能取消关注自己关注的用户
        params in request body:
            user: 被关注用户id
            follower: 发起关注用户id
        """
        if request.user.is_banned and not request.user.is_admin:
            return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
        try:
            follow = Follow.objects.get(follower_id=request.user, user_id=request.query_params.get('user'))
        except Follow.DoesNotExist:
            return Response({"detail": "该关注不存在"}, status=status.HTTP_404_NOT_FOUND)
        follow.delete()
        return Response({"status": "success"}, status=status.HTTP_204_NO_CONTENT)

@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def get_is_following(request):
    serializer = serializers.GetIsFollowingSerializer(data=request.query_params)
    if not serializer.is_valid():
        return Response(serializer.errors,status=status.HTTP_400_BAD_REQUEST)
    user_id = serializer.validated_data['user_id']
    self_id = request.user.id
    is_following = True
    try:
        Follow.objects.get(follower_id=self_id, user_id=user_id)
    except Follow.DoesNotExist:
        is_following = False
    return Response({'following':is_following})

@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def get_user_followers(request,user_id):
    #分页
    page_serializer = serializers.GetParamsPageSerializer(data=request.query_params)
    if not page_serializer.is_valid():
        return Response(page_serializer.errors,status=status.HTTP_400_BAD_REQUEST)
    page = page_serializer.validated_data['page']

    user:User
    try:
        user = User.objects.get(id=user_id)
    except User.DoesNotExist:
        return Response({"detail":"用户不存在"}, status=status.HTTP_404_NOT_FOUND)
    followers_query_set = Follow.objects.filter(user=user.id).select_related('follower')

    followers_result_set = CustomPagination.paginate_queryset(page,followers_query_set)
    followers_result = [follow.follower for follow in followers_result_set]
    result = serializers.GetUserFollowSerializer(followers_result,many=True).data
    return Response(result)

@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def get_user_followings(request,user_id):
    #分页
    page_serializer = serializers.GetParamsPageSerializer(data=request.query_params)
    if not page_serializer.is_valid():
        return Response(page_serializer.errors,status=status.HTTP_400_BAD_REQUEST)
    page = page_serializer.validated_data['page']

    user:User
    try:
        user = User.objects.get(id=user_id)
    except User.DoesNotExist:
        return Response({"detail":"用户不存在"}, status=status.HTTP_404_NOT_FOUND)
    followings_query_set = Follow.objects.filter(follower=user.id).select_related('user') 
    followings_query_set = CustomPagination.paginate_queryset(page,followings_query_set)
    followings_result = [follow.user for follow in followings_query_set]
    result = serializers.GetUserFollowSerializer(followings_result,many=True).data
    return Response(result)

#获取自己的粉丝
@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def get_self_followers(request):
    #分页
    page_serializer = serializers.GetParamsPageSerializer(data=request.query_params)
    if not page_serializer.is_valid():
        return Response(page_serializer.errors,status=status.HTTP_400_BAD_REQUEST)
    page = page_serializer.validated_data['page']

    followers_query_set = Follow.objects.filter(user=request.user.id).select_related('follower')
    followers_result_set = CustomPagination.paginate_queryset(page,followers_query_set)
    followers_result = [follow.follower for follow in followers_result_set]
    result = serializers.GetUserFollowSerializer(followers_result,many=True).data
    return Response(result)

#获取自己的关注
@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def get_self_followings(request):
    #分页
    page_serializer = serializers.GetParamsPageSerializer(data=request.query_params)
    if not page_serializer.is_valid():
        return Response(page_serializer.errors,status=status.HTTP_400_BAD_REQUEST)
    page = page_serializer.validated_data['page']

    followings_query_set = Follow.objects.filter(follower=request.user.id).select_related('user')

    followings_query_set = CustomPagination.paginate_queryset(page,followings_query_set)
    followings_result = [follow.user for follow in followings_query_set]
    result = serializers.GetUserFollowSerializer(followings_result,many=True).data
    return Response(result)