from rest_framework.decorators import api_view

from ..helpers import get_authing_client


@api_view(['POST'])
def send_sms_code(request):
    '''
    发送短信验证码
    params in query:
        phone: 手机号，必须
    '''
    client = get_authing_client()

    phone = request.body.get('phone')

    code = client.send_sms_code(phone)

    return code


@api_view(['POST'])
def send_verify_email(request) -> None:
    '''
    发送验证邮箱邮件
    params in body:
        email: 邮箱，必须
    '''
    client = get_authing_client()

    email = request.body.get('email')

    client.send_email(email, secene='VERIFY_EMAIL')


api_view(['POST'])
def send_rest_password_email(request) -> None:
    '''
    发送重置密码邮件
    params in body:
        email: 邮箱，必须
    '''
    client = get_authing_client()

    email = request.body.get('email')

    client.send_email(email, secene='REST_PASSWORD')


api_view(['POST'])
def send_change_email(request) -> None:
    '''
    发送更改邮箱邮件
    params in body:
        email: 邮箱，必须
    '''
    client = get_authing_client()

    email = request.body.get('email')

    client.send_email(email, secene='CHANGE_EMAIL')
