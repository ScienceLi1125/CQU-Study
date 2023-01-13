from django.db.models import  F
from rest_framework import status
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from rest_framework.permissions import IsAuthenticated
from rest_framework.views import APIView, Response

from first import serializers

from ..models import UserPost



from ..custom_authentication import AuthingIDAuthentication

from ..search import Search
from urllib.parse import unquote


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def search_post_content(request):
    key_words = request.query_params.get('key_words', None)
    if not key_words:
        return Response({"detail": "没有搜索关键词"}, status=status.HTTP_400_BAD_REQUEST)
    if len(key_words) < 2:
        return Response({"detail": "关键词长度至少为2"}, status=status.HTTP_400_BAD_REQUEST)
    if len(key_words) > 16:
        return Response({"detail": "关键词长度最多为16"}, status=status.HTTP_400_BAD_REQUEST)

    key_words = unquote(key_words)
    posts = UserPost.objects.filter(reply_to_id=None).filter(Search(F("post"), key_words))

    return Response(serializers.UserPostSerializer(posts, many=True).data)


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def search_post_title(request):
    key_words = request.query_params.get('key_words', None)
    if not key_words:
        return Response({"detail": "没有搜索关键词"}, status=status.HTTP_400_BAD_REQUEST)
    if len(key_words) < 2:
        return Response({"detail": "关键词长度至少为2"}, status=status.HTTP_400_BAD_REQUEST)
    if len(key_words) > 16:
        return Response({"detail": "关键词长度最多为16"}, status=status.HTTP_400_BAD_REQUEST)

    key_words = unquote(key_words)
    posts = UserPost.objects.filter(reply_to_id=None).filter(Search(F("title"), key_words))

    return Response(serializers.UserPostSerializer(posts, many=True).data)


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def search_post_full(request):
    key_words = request.query_params.get('key_words', None)
    if not key_words:
        return Response({"detail": "没有搜索关键词"}, status=status.HTTP_400_BAD_REQUEST)
    if len(key_words) < 2:
        return Response({"detail": "关键词长度至少为2"}, status=status.HTTP_400_BAD_REQUEST)
    if len(key_words) > 16:
        return Response({"detail": "关键词长度最多为16"}, status=status.HTTP_400_BAD_REQUEST)

    key_words = unquote(key_words)
    posts_title = UserPost.objects.filter(reply_to_id=None).filter(Search(F("title"), key_words))
    posts_content = UserPost.objects.filter(reply_to_id=None).filter(Search(F("post"), key_words))

    posts_title.union(posts_content)
    return Response(serializers.UserPostSerializer(posts_title, many=True).data)