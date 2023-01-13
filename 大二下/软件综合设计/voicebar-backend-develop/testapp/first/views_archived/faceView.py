import base64
from rest_framework import status
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from rest_framework.permissions import IsAuthenticated
from rest_framework.views import Response
from ..azureVoice.azureService import SpeechSynthesizer as SS
from ..face.face import face

from ..ip_adress import ipAddress

from first import serializers

from ..models import UserPost,UserAITest,UserImage,UserVoice
from ..tencent_cos.api import upload_file_cos,COSFileType


from ..custom_authentication import AuthingIDAuthentication

@api_view(['POST'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def face_to_mp3_post(request):
    """
    识别人脸图片
    给出评价
    并用结果生成音频
    params in request body:
        image: 图片base64编码
    """
    if request.user.is_banned and not request.user.is_admin:
        return Response({'status': 'error', 'message': '该账户已停用'}, status=status.HTTP_400_BAD_REQUEST)
    ss = SS()
    image_serializer = serializers.UploadPostImageSerializer(data=request.data)
    if not image_serializer.is_valid():
        return Response(image_serializer.errors,status=status.HTTP_400_BAD_REQUEST)
    image = image_serializer.validated_data['image']
    image_byte = image.read()
    if len(image_byte) > 2000000:
        return Response({"status": "faild", "detail": "请上传小于2MB的图片"}, status=status.HTTP_400_BAD_REQUEST)
    
    #人脸识别
    image_base64 = str(base64.b64encode(image_byte))[2:]
    try:
        comment, face_json = face(image_base64)
    except RuntimeError as e:
        return Response({"status": "faild", "detail": e.args[0]}, status=status.HTTP_400_BAD_REQUEST)
    #上传图片到cos
    image_url = upload_file_cos(file_type=COSFileType.AITEST,file_content=image_byte,file_extension='png',content_type=image.content_type)
    print(comment, face_json)
    emotion = face_json['emotion']
    mapping = {
        'bigsmile': 'cheerful',
        'anger': 'angry',
        'disgust': 'disgruntled',
        'fear': 'fearful',
        'happiness': 'cheerful',
        'neutral': 'neutral',
        'sadness': 'sad',
        'surprise': 'neutral'
    }
    style_choice = mapping.get(emotion, 'neutral')
    speaker = {'name': 'zh-CN-XiaoxiaoNeural'}
    style = {'style': style_choice}
    prosody = {'rate': 'medium', 'volume': 'medium', 'pitch': 'medium'}
    voice_url = ss.synthesize(
        text=comment,
        speaker=speaker,
        style=style,
        prosody=prosody
    )
    ai_result = {
        "age": face_json['age'],
        "gender": face_json['gender'],
        "glass": face_json['glass'],
        "mask": face_json['mask'],
        "score": face_json['score'],
        "emotion": face_json['emotion'],
    }
    ai_result_record = UserAITest(creator_id=request.user.id,json_result=ai_result,voice_url=voice_url,image_url=image_url)
    ai_result_record.save()
    return Response({"status": "success", "age": face_json['age'],
                        "gender": face_json['gender'],
                        "glass": face_json['glass'],
                        "mask": face_json['mask'],
                        "score": face_json['score'],
                        "emotion": face_json['emotion'],
                        "mp3_url": voice_url,
                        "result_id": ai_result_record.id},
                    status=status.HTTP_201_CREATED)

@api_view(['POST'])
@authentication_classes([AuthingIDAuthentication])
@permission_classes([IsAuthenticated])
def create_post_with_result_record(request):
    """
    使用人脸识别的结果记录发帖
    """
    TITLE_PREFIX = "[图片语音]"
    result_serializer = serializers.CreatePostFaceResultSerializer(data=request.data,context={'request': request})
    if not result_serializer.is_valid():
        return Response(result_serializer.errors,status=status.HTTP_400_BAD_REQUEST)
    result_id = result_serializer.validated_data['result_id']
    title = result_serializer.validated_data['title']
    result = UserAITest.objects.get(id=result_id)
    ip_loc = ipAddress.get_ip_loc(request)[0]
    #建帖子
    new_post = UserPost(user_id=request.user.id,title=TITLE_PREFIX+title,ip_loc=ip_loc)
    new_post.save()
    #绑定图片与语音
    post_image = UserImage(creator_id=request.user.id,image_url=result.image_url,post_id=new_post.id)
    post_image.save()
    post_voice = UserVoice(creator_id=request.user.id,voice_url=result.voice_url,post_id=new_post.id)
    post_voice.save()
    #删除记录
    result.delete()
    return Response({'status':'success'})