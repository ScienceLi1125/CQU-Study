from rest_framework import status
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from rest_framework.permissions import IsAuthenticated
from rest_framework.views import Response

from first import serializers
from ..custom_authentication import AuthingIDAuthentication

from ..models import Follow, UserPost, Like




@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def user_follower_count(request, user_id):
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    return Response({'count': Follow.objects.filter(user_id=user_id).count()})


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def user_following_count(request, user_id):
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    return Response({'count': Follow.objects.filter(follower_id=user_id).count()})


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def user_liked_count(request, user_id):
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    post_ids = UserPost.objects.filter(user=user_id).values_list('id', flat=True)
    return Response({'count': Like.objects.filter(post_id__in=post_ids).count()})


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def user_main_posts_count(request, user_id):
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    return Response({'count': UserPost.objects.filter(user_id=user_id, reply_to=None).count()})


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def user_comments_count(request, user_id):
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    return Response({'count': UserPost.objects.exclude(reply_to=None).filter(user_id=user_id).count()})


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def post_liked_count(request, post_id):
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    return Response({'count': Like.objects.filter(post_id=post_id).count()})


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def post_comment_count(request, post_id):
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    return Response({'count': UserPost.objects.exclude(reply_to=None).filter(reply_to=post_id).count()})


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def post_read_count(request, post_id):
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    return Response({'count': UserPost.objects.get(id=post_id).visited_count})
