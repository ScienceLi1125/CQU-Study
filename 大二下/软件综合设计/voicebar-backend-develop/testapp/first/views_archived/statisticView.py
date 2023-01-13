from ..custom_authentication import AuthingIDAuthentication

from rest_framework import status
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from rest_framework.permissions import IsAuthenticated
from rest_framework.views import Response

from ..models import UserPost, User
from django.db.models import F, Func
from django.db.models import Aggregate


from django.db.models import Count
from django.db.models.functions import ExtractHour

@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def get_posts_region_statistics(request):
    if not request.user.is_admin:
        return Response({"detail": "没有权限"}, status=status.HTTP_403_FORBIDDEN)
    posts = UserPost.objects\
                    .values('ip_loc')\
                    .annotate(count=Count('ip_loc'))\
                    .order_by('-count')
    return Response(posts)


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def get_posts_time_statistics(request):
    if not request.user.is_admin:
        return Response({"detail": "没有权限"}, status=status.HTTP_403_FORBIDDEN)

    posts = UserPost.objects\
                    .annotate(hour=ExtractHour('pub_date'))\
                    .values('hour')\
                    .annotate(num=Count('id'))\
                    .order_by('hour')

    return Response(posts)


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def get_users_post_count_statistics(request):
    if not request.user.is_admin:
        return Response({"detail": "没有权限"}, status=status.HTTP_403_FORBIDDEN)

    posts = UserPost.objects.values('user_id').annotate(cnt=Count('user_id')).order_by('-cnt')

    return Response(posts)


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def get_user_age_statistics(request):
    class AgeGroup(Func):
        template = '%(expressions)s div 10'

    if not request.user.is_admin:
        return Response({"detail": "没有权限"}, status=status.HTTP_403_FORBIDDEN)

    user_ages = User.objects.annotate(age_group=AgeGroup('age'))\
                            .values('age_group')\
                            .annotate(cnt=Count('id'))\
                            .order_by('age_group')

    return Response(user_ages)