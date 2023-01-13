
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from rest_framework.permissions import IsAuthenticated
from rest_framework.views import Response



from ..custom_authentication import AuthingIDAuthentication

from ..ip_adress import ipAddress


@api_view(['GET'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def get_ip_loc(request):
    """
    将ip地址转换为地理位置
    """
    addr, desc = ipAddress.get_ip_loc(request)
    return Response({'addr': addr, 'desc': desc})