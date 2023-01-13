

from django.db import IntegrityError

from rest_framework import status
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from rest_framework.permissions import IsAuthenticated
from rest_framework.views import APIView, Response

from first import serializers
from ..models import UserPost, Like

from ..custom_authentication import AuthingIDAuthentication




class LikeView(APIView):
    authentication_classes = (AuthingIDAuthentication,)
    permission_classes = (IsAuthenticated,)

    def post(self, request, post_id):
        """
        用户点赞帖子
        params in restful url:
            post_id: 帖子id
        """
        # post_id = request.data.get('post_id')
        if request.user.is_banned and not request.user.is_admin:
            return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
        try:
            post = UserPost.objects.get(id=post_id)
        except UserPost.DoesNotExist:
            return Response({"detail": "该帖子不存在"}, status=status.HTTP_404_NOT_FOUND)
        try:
            like = Like.objects.create(user=request.user, post=post)
        except IntegrityError:
            return Response({"detail": "不能重复点赞"}, status=status.HTTP_400_BAD_REQUEST)
        return Response(serializers.LikeSerializer(like).data, status=status.HTTP_201_CREATED)

    def delete(self, request, post_id):
        """
        取消点赞
        params in request body:
            post_id: 帖子id
        """
        # post_id = request.data.get('post_id')
        if request.user.is_banned and not request.user.is_admin:
            return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
        try:
            post = UserPost.objects.get(id=post_id)
        except UserPost.DoesNotExist:
            return Response({"detail": "该帖子不存在"}, status=status.HTTP_404_NOT_FOUND)
        like = Like.objects.filter(user=request.user, post=post)
        if not like:
            return Response({"detail": "没有点赞"}, status=status.HTTP_400_BAD_REQUEST)
        like.delete()
        return Response({"status": "success"}, status=status.HTTP_204_NO_CONTENT)



@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def user_like_list(request):
    """
    返回用户点赞的帖子列表
    params in query parameters:
        page: 页码（可选，默认为1）
    """
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    ITEM_PER_PAGE = 10
    page = request.query_params.get('page', '1')
    page = int(page)
    start_offset = (page - 1) * ITEM_PER_PAGE

    return Response(serializers.LikeSerializer(
        Like.objects.filter(user=request.user)[start_offset:start_offset + ITEM_PER_PAGE],
        many=True
    ).data)



@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def is_post_liked(request, post_id):
    """
    判断用户是否点赞了帖子
    params in query parameters:
        post_id: 帖子id
    """
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)

    try:
        post = UserPost.objects.get(id=post_id)
    except UserPost.DoesNotExist:
        return Response({"detail": "帖子不存在"}, status=status.HTTP_400_BAD_REQUEST)

    if Like.objects.filter(user=request.user, post=post).exists():
        return Response({"status": "success", "liked": True}, status=status.HTTP_200_OK)
    else:
        return Response({"status": "success", "liked": False}, status=status.HTTP_200_OK)