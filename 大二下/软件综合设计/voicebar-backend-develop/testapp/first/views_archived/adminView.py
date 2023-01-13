
from rest_framework import status
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from rest_framework.permissions import IsAuthenticated
from rest_framework.views import Response

from first import serializers
from ..models import User, Follow, Like, UserPost
from ..custom_authentication import AuthingIDAuthentication

import authing
from authing.v2.management import ManagementClient, ManagementClientOptions

@api_view(['POST'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def ban_user(request, user_id):
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    if request.user.is_admin is False:
        return Response({'status': 'error', 'message': '没有权限'}, status=status.HTTP_400_BAD_REQUEST)
    try:
        user = User.objects.get(id=user_id)
        if user.is_admin:
            return Response({'status': 'error', 'message': '不能禁用管理员'}, status=status.HTTP_400_BAD_REQUEST)
    except User.DoesNotExist:
        return Response({'status': 'error', 'message': '用户不存在'}, status=status.HTTP_400_BAD_REQUEST)
    user.is_banned = True
    user.save()
    return Response({'status': 'success'})


@api_view(['POST'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def unban_user(request, user_id):
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    if request.user.is_admin is False:
        return Response({'status': 'error', 'message': '没有权限'}, status=status.HTTP_400_BAD_REQUEST)
    try:
        user = User.objects.get(id=user_id)
    except User.DoesNotExist:
        return Response({'status': 'error', 'message': '用户不存在'}, status=status.HTTP_400_BAD_REQUEST)
    user.is_banned = False
    user.save()
    return Response({'status': 'success'})

@api_view(['DELETE'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def delete_user(request, user_id):
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    if request.user.is_admin is False:
        return Response({'status': 'error', 'message': '没有权限'}, status=status.HTTP_400_BAD_REQUEST)
    try:
        user = User.objects.get(id=user_id)
    except User.DoesNotExist:
        return Response({'status': 'error', 'message': '用户不存在'}, status=status.HTTP_400_BAD_REQUEST)

    management_client = ManagementClient(
        options=ManagementClientOptions(
            user_pool_id='62de9db90657ee4f590d7365',
            secret='af0ce9888e14d3247892655997612c24',
        ))

    try:
        management_client.users.delete(userId=user.authingid)
        user.delete()
        return Response({'status': 'success'})
    except authing.v2.exceptions.AuthingException as e:
        if e.code == 2004:
            user.delete()
            return Response({'status': 'success'})
        return Response({'status': 'error','detail':str(e)},status=status.HTTP_400_BAD_REQUEST)


