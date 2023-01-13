from authing.v2.authentication import AuthenticationClient, AuthenticationClientOptions


def get_authing_client():
    return AuthenticationClient(
        options=AuthenticationClientOptions(
            app_id='62de9dba412eabb062f40ab2',
            app_host='https://aiekefnkoldmbnng-demo.authing.cn',
            secret='e3a5bf5174e0630b6c9a0cb9ce9fcd29',
            protocol='oidc'
        ))
