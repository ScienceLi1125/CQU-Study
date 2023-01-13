# -*- encoding: utf-8 -*-
"""
@Modify Time          @Author      @Version    @Description
--------------      -----------    --------    ------------
2022/8/13 9:30     chuxiaodong      1.0           None
"""
import json

import requests

emo_dist = {'anger': '您似乎有点生气，我该——怎么让你开心起来呢？',
            'disgust': '您在厌恶一些东西吗？我该——怎么让你开心起来呢？',
            'fear': '您在恐惧一些东西吗？勇敢一点！',
            'happiness': '您看起来很高兴！和我分享一下遇到的开心事呗。',
            'neutral': '您的表情很自然，再笑一笑也许更好看哦！',
            'sadness': '您似乎有点伤心……我该——怎么让你开心起来呢？',
            'surprise': '这张照片是偷拍的吗？好过分！您看起来，也有些惊讶呢。'
            }
api_key = "FMBYzaZmTQdGP7QqPFYXNLIeATAiREn1"
api_secret = "yy8Tab4HpKigE9SauzuQ0PRkl-NlNedy"
return_attributes = "gender,age,emotion,eyestatus,mouthstatus," \
                    "smiling,blur,facequality,beauty,skinstatus"
url = "https://api-cn.faceplusplus.com/facepp/v3/detect"
re_json = {"age": 0,
           'gender': 0,
           'glass': False,
           'mask': False,
           'score': 100,
           "emotion": 'happiness',
           }


def face(img_base64):
    """
    Args:
        img_base64: base64编码的图片,小于2mb,有且只有一张人脸
    Returns:[人脸信息文本，
            re_json = {
            "age": int,
            'gender': int, 2:男,3:女，
            'glass': bool,
           'mask': bool,
           'score': int, 颜值评分
           "emotion": str,  #'anger','disgust','fear','happiness','neutral','sadness','surprise','bigsmile'
           }
           ]
    或raise错误Runtimeerror
    """
    params = {
        'api_key': api_key,
        'api_secret': api_secret,
        'image_base64': img_base64,
        'return_attributes': return_attributes,
    }
    r = requests.post(url=url, data=params)

    if r.status_code == 400:
        raise RuntimeError("对不起，您上传的图片暂时不受支持，换一张试试吧\n请注意，照片大小不能超过2MB，照片上有且只有一张人脸。")
    if r.status_code != 200:
        raise RuntimeError("网络错误，请稍后再试")

    try:
        person = json.loads(r.text)
        person = person['faces'][0]['attributes']
        comment = ""

        if person['blur']['blurness']['value'] > 80:
            comment = comment + '图片太模糊了，让我猜猜……'
        elif person['blur']['blurness']['value'] > 50 or person['blur']['motionblur']['value'] > 60 or \
                person['blur']['gaussianblur']['value'] > 70 or person['facequality']['value'] < 60:
            comment = comment + '您的图片有点模糊，不过我——还是很相信我的直觉的。'

        if person['age']['value'] < 18:
            if person['gender']['value'] == 'Male':
                comment = comment + "小帅哥，"
                classes = 1
            else:
                comment = comment + "小美女，"
                classes = 4
            comment = comment + "好可爱！"
        elif person['age']['value'] < 60:
            if person['gender']['value'] == 'Male':
                comment = comment + "先生，"
                classes = 2
            else:
                comment = comment + "女士，"
                classes = 5
            comment = comment + "您今天看起来很年轻呢！"
        else:
            if person['gender']['value'] == 'Male':
                comment = comment + "爷爷，"
                classes = 3
            else:
                comment = comment + "奶奶，"
                classes = 6
            comment = comment + "您今天看起来很精神呢！"

        re_json['age'] = person['age']['value']
        if classes <= 3:
            re_json['gender'] = 2
        else:
            re_json['gender'] = 3

        if classes <= 3:
            sum = float(person['beauty']['male_score'])
            sum = int((sum / 2.5) + 60)  # 防止分数过低
            if sum > 90:
                comment = comment + "您好帅气，我保守估计，您比百分之" + str(sum) + "的男性都好看！"
            else:
                comment = comment + "您好帅气！"
            re_json['score'] = sum
        else:
            sum = float(person['beauty']['female_score'])
            sum = int((sum / 2.5) + 60)  # 防止分数过低
            if sum > 90:
                comment = comment + "您好漂亮，我保守估计，您比百分之" + str(sum) + "的女性都好看！"
            else:
                comment = comment + "您好漂亮！"
            re_json['score'] = sum

        if person['skinstatus']['health'] > 50:
            comment = comment + "您气色红润，看起来很健康！"
        elif person['skinstatus']['dark_circle'] > 50:
            comment = comment + "不过，您似乎有黑眼圈，要早点休息哦！"
            if classes == 1 or classes == 4:
                comment = comment + '小朋友晚上可不能贪玩哦！'
            elif classes == 2 or classes == 5:
                comment = comment + "身体才是革命的本钱！"

        sum = [
            person['eyestatus']['left_eye_status']['occlusion'] + person['eyestatus']['right_eye_status']['occlusion'],
            person['eyestatus']['left_eye_status']['normal_glass_eye_open'] + person['eyestatus']['left_eye_status'][
                'normal_glass_eye_close'] + \
            person['eyestatus']['right_eye_status']['normal_glass_eye_open'] + person['eyestatus']['right_eye_status'][
                'normal_glass_eye_close'],
            person['eyestatus']['left_eye_status']['dark_glasses'] + person['eyestatus']['right_eye_status'][
                'dark_glasses'],
            person['eyestatus']['left_eye_status']['no_glass_eye_open'] + person['eyestatus']['right_eye_status'][
                'no_glass_eye_open']
        ]
        sum = sum.index(max(sum))
        if sum == 0:
            comment = comment + "您的眼睛似乎被什么东西遮挡了。"
        elif sum == 1:
            comment = comment + "您戴着一副眼镜。"
            re_json['glass'] = True
            if classes == 1 or classes == 4:
                comment = comment + "小朋友要注意保护眼镜哦！"
        elif sum == 2:
            comment = comment + "您带着一副墨镜。"
            re_json['glass'] = True
        elif sum == 3:
            comment = comment + "您没有带眼镜。好羡慕您的视力啊！"
            re_json['glass'] = False
        else:
            comment = comment + "您没有带眼镜。不过，拍照时睁大你的眼镜会更好看的！"
            re_json['glass'] = False

        if person['mouthstatus']['surgical_mask_or_respirator'] > 50:
            comment = comment + '您似乎戴了口罩。感谢您为疫情防控做出的贡献。'
            re_json['mask'] = True
        else:
            re_json['mask'] = False

        if person['smile']['value'] > 70:
            comment = comment + "照片上的您笑的好开心啊！您看起来很高兴！和我分享一下遇到的开心事呗。"
            re_json['emotion'] = 'bigsmile'
        else:
            sum = person['emotion'].items()
            sum = max(sum, key=lambda x: x[1])[0]

            re_json['emotion'] = str(sum)

            sum = emo_dist[str(sum)]
            comment = comment + sum

        comment = comment + "感谢您使用我们的语音心情服务！"
        return comment, re_json
    except:
        raise RuntimeError("对不起，图片上没有检测出人脸")
