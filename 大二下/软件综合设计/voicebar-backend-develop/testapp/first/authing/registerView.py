from rest_framework.decorators import api_view
from rest_framework.views import APIView, Response
from ..helpers import get_authing_client
from rest_framework import status
from ..serializers import UserSerializer

from ..models import User


@api_view(['POST'])
def register_by_email(request):
    '''
    通过邮箱注册
    params in body:
        email: 邮箱，必须
        password: 密码，必须
        nickname: 昵称，可选


    '''
    client = get_authing_client()

    email = request.data.get('email')
    password = request.data.get('password')
    nickname = request.data.get('nickname', None)
    profile = {'nickname': nickname} if nickname else None
    # user = client.register_by_email(email, password, profile)
    user:dict = client.login_by_email(email, password)

    user = {
        'authingid': user['id'],
        'nickname': user.get('nickname') if user.get('nickname') else '新用户',
        'motto': '哥是一个传说',
    }
    print(user)
    serializer = UserSerializer(data=user)

    if serializer.is_valid():
        serializer.save()
        return Response(
            {"user_info": serializer.data},
            status=status.HTTP_201_CREATED
        )
    else:
        return Response(
            {"error": serializer.errors},
            status=status.HTTP_400_BAD_REQUEST
        )


@api_view(['POST'])
def register_by_phone_code(request):
    '''
    通过手机号和手机验证码注册
    params in body:
        phone: 手机号，必须
        code: 验证码，必须
        password: 密码，必须
        nickname: 昵称，可选
    '''
    client = get_authing_client()

    phone = request.data.get('phone')
    code = request.data.get('code')
    password = request.data.get('password')
    nickname = request.data.get('nickname', None)
    profile = {'nickname': nickname} if nickname else None
    user = client.register_by_phone_code(phone, code, password, profile)

    return user
