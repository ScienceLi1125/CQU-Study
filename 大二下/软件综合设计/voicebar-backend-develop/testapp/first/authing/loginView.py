from rest_framework.decorators import api_view

from ..helpers import get_authing_client


@api_view(['POST'])
def login_by_email(request):
    '''
    通过邮箱登录
    未配置图形验证码
    params in body:
        email: 邮箱，必须
        password: 密码，必须
    '''
    client = get_authing_client()

    email = request.data.get('email')
    password = request.data.get('password')
    user = client.login_by_email(email, password)

    return user


@api_view(['POST'])
def login_by_phone_code(request):
    '''
    通过手机号和手机验证码登录
    未配置图形验证码
    params in body:
        phone: 手机号，必须
        code: 验证码，必须
        password: 密码，必须
    '''
    client = get_authing_client()

    phone = request.data.get('phone')
    code = request.data.get('code')
    password = request.data.get('password')
    user = client.login_by_phone_code(phone, code, password)

    return user


@api_view(['GET'])
def get_user_info(request):
    '''
    获取用户信息
    '''
    client = get_authing_client()

    user = client.get_current_user(request.user.id)

    return user


@api_view(['POST'])
def logout(request):
    '''
    退出登录
    '''
    client = get_authing_client()

    client.logout(request.user.id)

    return None