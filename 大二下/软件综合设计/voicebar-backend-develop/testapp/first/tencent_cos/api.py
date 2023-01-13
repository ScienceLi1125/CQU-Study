from qcloud_cos import CosConfig
from qcloud_cos import CosS3Client
from enum import Enum, auto
from typing import Union
import uuid

#请使用Enum来表示上传的文件类型
class COSFileType(Enum):
    AVATAR = auto()
    ARTICLE_IMAGE = auto()
    VOICE = auto()
    AITEST = auto()

# 1. 设置用户属性, 包括 secret_id, secret_key, region等。Appid 已在CosConfig中移除，请在参数 Bucket 中带上 Appid。Bucket 由 BucketName-Appid 组成
secret_id = 'AKIDPcaIjuoSpvlLehTyC9pGRLyKQFoIZaMs' 
secret_key = 'IK6dvylJcfSzJNBj12mEQN5XljRwCDyT'
region = 'ap-shanghai'

token = None
scheme = 'https'

config = CosConfig(Region=region, SecretId=secret_id, SecretKey=secret_key, Token=token, Scheme=scheme)
client = CosS3Client(config)

bucket_name = 'voicebar-1251996605'
bucket_access_url = 'https://cos.randeweb.cn'

def upload_file_cos(file_type: COSFileType,file_content: bytes,file_extension:str,content_type:Union[None,str]) -> str:
    '''
    指定文件类型,传入二进制数据,将文件上传至对象存储,并返回文件访问URL
    '''
    upload_dir = ''
    if file_type == COSFileType.AVATAR:
        upload_dir = 'avatar'
    elif file_type == COSFileType.ARTICLE_IMAGE:
        upload_dir = 'article_image'
    elif file_type == COSFileType.VOICE:
        upload_dir = 'voice'
    elif file_type == COSFileType.AITEST:
        upload_dir = 'ai_test'
    
    unique_name = uuid.uuid4()
    headers = {}
    if content_type:
        headers['ContentType'] = content_type

    client.put_object(
        Bucket=bucket_name,
        Body=file_content,
        Key=f'{upload_dir}/{unique_name}.{file_extension}',
        EnableMD5=False,
        **headers
    )

    return f'{bucket_access_url}/{upload_dir}/{unique_name}.{file_extension}'