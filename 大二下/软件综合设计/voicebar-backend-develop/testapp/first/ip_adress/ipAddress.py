from qqwry import updateQQwry
from qqwry import QQwry
from os.path import dirname, abspath


# X-Forwarded-For:简称XFF头，它代表客户端，也就是HTTP的请求端真实的IP，只有在通过了HTTP 代理或者负载均衡服务器时才会添加该项。
def get_ip(request):
    '''获取请求者的IP信息'''
    x_forwarded_for = request.META.get('HTTP_X_FORWARDED_FOR')  # 判断是否使用代理
    if x_forwarded_for:
        ip = x_forwarded_for.split(',')[0]  # 使用代理获取真实的ip
    else:
        ip = request.META.get('REMOTE_ADDR')  # 未使用代理获取IP
    return ip


def update_ip_address():
    file_name = 'qqwry.dat'
    ret = updateQQwry(file_name)


def get_ip_loc(request):
    q = QQwry()
    data_file_path = abspath(dirname(__file__)) + '/qqwry.dat'
    q.load_file(data_file_path)
    ip = get_ip(request)
    # print(q.lookup(ip))
    # print(type(q.lookup(ip)))
    return q.lookup(ip)


if __name__ == '__main__':
    q = QQwry()
    data_file_path = abspath(dirname(__file__)) + '/qqwry.dat'
    q.load_file(data_file_path)
    print(q.lookup('183.226.75.16'))