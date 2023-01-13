from rest_framework_simplejwt.authentication import JWTAuthentication
from .helpers import get_authing_client
from .models import User

import base64
import json

from rest_framework.permissions import IsAuthenticated

def get_authingid_from_token(id_token:str):
    '''
    在本地解码ID_TOKEN并返回其中的ID
    不用网络请求,增加服务器处理请求的效率
    '''
    token_parts = id_token.split('.')
    try:
        if len(token_parts) == 3: #其他情况不用管,过不了check_login_status
            if len(token_parts[1]) % 4:
                #对齐
                # not a multiple of 4, add padding:
                token_parts[1] += '=' * (4 - len(token_parts[1]) % 4) 
            result_bytes = base64.b64decode(token_parts[1])
            return json.loads(result_bytes).get('sub',-1)
    except Exception: #格式错误
        return None

class AuthingIDAuthentication(JWTAuthentication):
    """
    使用Authing在线接口验证Token的合法性,
    并从Token中提取用户信息,用户权限
    """

    # 只需重载authenticate方法
    def authenticate(self, request):
        header = self.get_header(request)
        if header is None:
            return None
        raw_token = self.get_raw_token(header)
        raw_token = str(raw_token, encoding='utf-8')
        # 在线验证
        client = get_authing_client()
        authingid = get_authingid_from_token(raw_token)
        data = client.check_login_status(token=raw_token)
        if data.get('code', 200) != 200:  # Token未登录
            return None
        # 接着根据ID从数据库中返回用户
        user, created = User.objects.get_or_create(authingid=authingid)
        user.is_authenticated = True
        return user, None
