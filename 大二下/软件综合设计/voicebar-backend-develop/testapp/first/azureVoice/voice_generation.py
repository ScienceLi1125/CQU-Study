from .azureService import SpeechSynthesizer as SS

VOICE_OPTIONS_DISPLAY = [
    {
        "name": "晓晓(女青年)",
        "styles": ["通用","语音助手", "聊天", "客户服务", "新闻广播", "温柔亲切的", "生气的", "冷静的", "高兴的",
                    "不满的", "害怕的", "温和的", "抒情的", "伤心的", "严肃的", "诗歌朗诵"],
    },
    {
        "name": "晓双(小女孩)",
        "styles": ["通用","聊天"],
    },
    {
        "name": "晓秋(成熟女性)",
        "styles": ["通用"],
    },
    {
        "name": "云希(男青年)",
        "styles": ["通用","叙述(放松的)","不安的","害怕的","高兴的","不满的","严肃的","生气的","伤心的","忧伤的",
                   "聊天","语音助手","新闻广播"],
    },
    {
        "name": "云扬(成熟男性)",
        "styles": ["通用","客户服务","叙述(专业的)","新闻广播(随意的)"],
    },
    {
        "name": "云希(小男孩)",
        "styles": ["通用","叙述(放松的)","不安的","害怕的","高兴的","不满的","严肃的","生气的","伤心的","忧伤的",
                   "聊天","语音助手","新闻广播"],
    }
]

VOICE_OPTIONS = [
    {
        "name": "zh-CN-XiaoxiaoNeural",
        "styles": ["general","assistant", "chat", "customerservice", "newscast", "affectionate", "angry", "calm", "cheerful",
                    "disgruntled", "fearful", "gentle", "lyrical", "sad", "serious", "poetry-reading"],
    },
    {
        "name": "zh-CN-XiaoshuangNeural",
        "styles": ["general","chat"],
    },
    {
        "name": "zh-CN-XiaoqiuNeural",
        "styles": ["general"],
    },
    {
        "name": "zh-CN-YunxiNeural",
        "styles": ["general","narration-relaxed","embarrassed","fearful","cheerful","disgruntled","serious","angry","sad","depressed",
                "chat","assistant","newscast"],
    },
    {
        "name": "zh-CN-YunyangNeural",
        "styles": ["general","customerservice","narration-professional","newscast-casual"],
    },
    {
        "name": "zh-CN-YunXiNeural",
        "styles": ["general","narration-relaxed","embarrassed","fearful","cheerful","disgruntled","serious","angry","sad","depressed",
                "chat","assistant","newscast"],
    }
]

def validate_options(speaker_id:int,style_id:int) -> bool:
    #验证speaker_id是否可用
    if speaker_id < 0 or speaker_id >= len(VOICE_OPTIONS):
        return False
    speaker_options = VOICE_OPTIONS[speaker_id]
    if style_id < 0 or style_id >= len(speaker_options['styles']):
        return False
    return True

#临时调试用语音处理
def generate_voice(content,speaker_id,style_id):
    ss = SS()
    #使用此函数前需验证speaker_id与style_id的有效性
    speaker_options = VOICE_OPTIONS[speaker_id]
    style = {'style': 'affectionate', 'styledegree': '1'}
    styles = speaker_options["styles"]
    styles_mapping = dict(zip(range(len(styles)), styles))
    style['style'] = styles_mapping[style_id]
    if speaker_id == 5: #小男孩
        style['role'] = "Boy"

    speaker = {'name': speaker_options['name']}

    url = ss.synthesize(
        text=content,
        speaker=speaker,
        style=style,
        prosody={'rate': 'medium', 'volume': 'medium', 'pitch': 'medium'}
    )
    return url


