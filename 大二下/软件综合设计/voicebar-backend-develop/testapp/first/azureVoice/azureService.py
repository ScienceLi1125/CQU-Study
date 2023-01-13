import xml.etree.ElementTree as ET
from os.path import abspath, dirname
from typing import Dict

import azure.cognitiveservices.speech as speechsdk

speech_key = "b078245957a24f038997c9dda6a67df6"
service_region = "eastasia"


def text_to_mp3(text: str) -> None:
    """
    使用Azure的Speech SDK将文本转换为MP3文件
    text: 要转换的文本
    """

    speech_config = speechsdk.SpeechConfig(subscription=speech_key, region=service_region)
    language = "zh-CN"
    speech_config.speech_synthesis_language = language
    voice = "Microsoft Server Speech Text to Speech Voice (zh-CN, XiaoshuangNeural)"
    speech_config.speech_synthesis_voice_name = voice
    speech_config.set_speech_synthesis_output_format(speechsdk.SpeechSynthesisOutputFormat.Audio16Khz32KBitRateMonoMp3)

    file_name = dirname(dirname(abspath(__file__))) + "/output/text_output.mp3"
    file_config = speechsdk.audio.AudioOutputConfig(filename=file_name)

    speech_synthesizer = speechsdk.SpeechSynthesizer(speech_config=speech_config, audio_config=file_config)

    result = speech_synthesizer.speak_text_async(text).get()

    # Check result
    if result.reason == speechsdk.ResultReason.SynthesizingAudioCompleted:
        print("Speech synthesized for text [{}], and the audio was saved to [{}]".format(text, file_name))
    elif result.reason == speechsdk.ResultReason.Canceled:
        cancellation_details = result.cancellation_details
        print("Speech synthesis canceled: {}".format(cancellation_details.reason))
        if cancellation_details.reason == speechsdk.CancellationReason.Error:
            print("Error details: {}".format(cancellation_details.error_details))


def ssml_file_to_mp3() -> None:
    """
    使用Azure的Speech SDK将文本转换为MP3文件
    使用SSML格式，可以添加语调感情等

    """

    speech_config = speechsdk.SpeechConfig(subscription=speech_key, region=service_region)
    language = "zh-CN"
    speech_config.speech_synthesis_language = language
    voice = "Microsoft Server Speech Text to Speech Voice (zh-CN, XiaoshuangNeural)"
    speech_config.speech_synthesis_voice_name = voice
    speech_config.set_speech_synthesis_output_format(speechsdk.SpeechSynthesisOutputFormat.Audio16Khz32KBitRateMonoMp3)

    file_name = dirname(dirname(abspath(__file__))) + "/output/ssml_output.mp3"
    file_config = speechsdk.audio.AudioOutputConfig(filename=file_name)
    speech_synthesizer = speechsdk.SpeechSynthesizer(speech_config=speech_config, audio_config=file_config)

    ssml_text = ""
    ssml_path = dirname(abspath(__file__)) + "/test.xml"
    with open(ssml_path, 'r', encoding='UTF-8') as f:
        ssml_text = f.read()
    result = speech_synthesizer.speak_ssml_async(ssml_text).get()

    # Check result
    if result.reason == speechsdk.ResultReason.SynthesizingAudioCompleted:
        print("the audio was saved to [{}]".format(file_name))
    elif result.reason == speechsdk.ResultReason.Canceled:
        cancellation_details = result.cancellation_details
        print("Speech synthesis canceled: {}".format(cancellation_details.reason))
        if cancellation_details.reason == speechsdk.CancellationReason.Error:
            print("Error details: {}".format(cancellation_details.error_details))


def text_to_mp3_costume_voice(text: str, voiceNo: int = 0) -> None:
    """
    使用Azure的Speech SDK将文本转换为MP3文件
    text: 要转换的文本

    """

    speech_config = speechsdk.SpeechConfig(subscription=speech_key, region=service_region)
    language = "zh-CN"
    speech_config.speech_synthesis_language = language

    switch_voice = {
        0: "zh-CN, XiaoxiaoNeural",
        1: "zh-CN, XiaoshuangNeural",
        2: "zh-CN, XiaoruiNeural",
        3: "zh-CN, YunxiNeural",
        4: "zh-CN, YunyangNeural",
    }
    voice_chosen = switch_voice.get(voiceNo, "zh-CN, XiaoxiaoNeural")
    voice = f"Microsoft Server Speech Text to Speech Voice ({voice_chosen})"
    speech_config.speech_synthesis_voice_name = voice

    speech_config.set_speech_synthesis_output_format(speechsdk.SpeechSynthesisOutputFormat.Audio16Khz32KBitRateMonoMp3)

    file_name = dirname(dirname(abspath(__file__))) + "/output/costume_voice_output.mp3"
    file_config = speechsdk.audio.AudioOutputConfig(filename=file_name)

    speech_synthesizer = speechsdk.SpeechSynthesizer(speech_config=speech_config, audio_config=file_config)

    result = speech_synthesizer.speak_text_async(text).get()

    # Check result
    if result.reason == speechsdk.ResultReason.SynthesizingAudioCompleted:
        print("Speech synthesized for text [{}], and the audio was saved to [{}]".format(text, file_name))
    elif result.reason == speechsdk.ResultReason.Canceled:
        cancellation_details = result.cancellation_details
        print("Speech synthesis canceled: {}".format(cancellation_details.reason))
        if cancellation_details.reason == speechsdk.CancellationReason.Error:
            print("Error details: {}".format(cancellation_details.error_details))


def ssml_file_to_mp3_costume_voice(text: str, speaker: Dict[str, str], style: Dict[str, str],
                                   prosody: Dict[str, str]) -> None:
    """
    使用Azure的Speech SDK将文本转换为MP3文件
    使用SSML格式，可以添加语调感情等
    params:
        text: 要转换的文本
        speaker: 语音发音人，字典，格式类似 {'name': 'zh-CN-XiaomoNeural'}
        style: 语音情感，可特定情感强度，字典，格式类似 {'style': 'calm', 'styledegree': '2'}
        prosody: 语音语调，可特定语速、音量、音高，字典，格式类似 {'rate': 'fast', 'volume': 'medium', 'pitch': 'low'}
    """

    speech_config = speechsdk.SpeechConfig(subscription=speech_key, region=service_region)
    language = "zh-CN"
    speech_config.speech_synthesis_language = language
    voice = "Microsoft Server Speech Text to Speech Voice (zh-CN, XiaoxiaoNeural)"
    speech_config.speech_synthesis_voice_name = voice
    speech_config.set_speech_synthesis_output_format(speechsdk.SpeechSynthesisOutputFormat.Audio16Khz32KBitRateMonoMp3)

    # 读取xml文件，定制化语音
    file = dirname(abspath(__file__)) + "/costume.xml"
    tree = ET.parse(file)
    root = tree.getroot()

    ET.register_namespace("mstts", "http://www.w3.org/2001/mstts")
    root[0][0][0].text = text  # 更改文本
    root[0].attrib = speaker  # 更改说话人
    root[0][0].attrib = style  # 更改语音风格
    root[0][0][0].attrib = prosody  # 更改语调

    file_name = dirname(dirname(abspath(__file__))) + "/output/ssml_costume_output.mp3"
    file_config = speechsdk.audio.AudioOutputConfig(filename=file_name)
    speech_synthesizer = speechsdk.SpeechSynthesizer(speech_config=speech_config, audio_config=file_config)

    ssml_text = ET.tostring(root, encoding='unicode')
    result = speech_synthesizer.speak_ssml_async(ssml_text).get()

    # 检查延迟
    # first byte latency	指示开始合成与接收第一个音频区块之间的时间延迟
    # finish latency	指示开始合成与接收全部合成音频之间的时间延迟。
    first_byte_latency = int(
        result.properties.get_property(speechsdk.PropertyId.SpeechServiceResponse_SynthesisFirstByteLatencyMs))
    finished_latency = int(
        result.properties.get_property(speechsdk.PropertyId.SpeechServiceResponse_SynthesisFinishLatencyMs))
    print("First byte latency: {}".format(first_byte_latency))
    print("Finished latency: {}".format(finished_latency))

    # Check result
    if result.reason == speechsdk.ResultReason.SynthesizingAudioCompleted:
        print("the audio was saved to [{}]".format(file_name))
    elif result.reason == speechsdk.ResultReason.Canceled:
        cancellation_details = result.cancellation_details
        print("Speech synthesis canceled: {}".format(cancellation_details.reason))
        if cancellation_details.reason == speechsdk.CancellationReason.Error:
            print("Error details: {}".format(cancellation_details.error_details))

from ..tencent_cos.api import upload_file_cos
from ..tencent_cos.api import COSFileType
class SpeechSynthesizer:
    def __init__(self):
        # 初始化配置

        # 配置配音人 speech_config
        self.speech_config = speechsdk.SpeechConfig(subscription=speech_key, region=service_region)
        language = "zh-CN"
        voice = "Microsoft Server Speech Text to Speech Voice (zh-CN, XiaoxiaoNeural)"

        self.speech_config.speech_synthesis_language = language
        self.speech_config.speech_synthesis_voice_name = voice
        self.speech_config.set_speech_synthesis_output_format(
            speechsdk.SpeechSynthesisOutputFormat.Audio16Khz32KBitRateMonoMp3)

        # # 配置输出路径，将输出写到本地 audio_config
        # self.file_name = path
        # self.file_config = speechsdk.audio.AudioOutputConfig(filename=self.file_name)

        # self.speech_synthesizer = speechsdk.SpeechSynthesizer(speech_config=self.speech_config,
        #                                                       audio_config=self.file_config)

        #  将输出写到内存中
        self.speech_synthesizer = speechsdk.SpeechSynthesizer(speech_config=self.speech_config, audio_config=None)

        self.connection = speechsdk.Connection.from_speech_synthesizer(self.speech_synthesizer)
        self.connection.open(True)

        print("SS instance created.")

    def synthesize(self, text: str, speaker: Dict[str, str], style: Dict[str, str], prosody: Dict[str, str]) -> str:
        """
        使用Azure的Speech SDK将文本转换为MP3文件
        使用SSML格式，可以添加语调感情等
        params:
            text: 要转换的文本
            speaker: 语音发音人，字典，格式类似 {'name': 'zh-CN-XiaomoNeural'}
            style: 语音情感，可特定情感强度，字典，格式类似 {'style': 'calm', 'styledegree': '2'}
            prosody: 语音语调，可特定语速、音量、音高，字典，格式类似 {'rate': 'fast', 'volume': 'medium', 'pitch': 'low'}
        """

        # 读取xml文件，定制化语音
        file = dirname(abspath(__file__)) + "/costume.xml"
        tree = ET.parse(file)
        root = tree.getroot()

        ET.register_namespace("mstts", "http://www.w3.org/2001/mstts")
        root[0][0][0].text = text  # 更改文本
        root[0].attrib = speaker  # 更改说话人
        root[0][0].attrib = style  # 更改语音风格
        root[0][0][0].attrib = prosody  # 更改语调

        result = self.speech_synthesizer.speak_ssml_async(ET.tostring(root, encoding='unicode')).get()

        # Check result
        if result.reason == speechsdk.ResultReason.SynthesizingAudioCompleted:
            # print("the audio was saved to [{}]".format(self.file_name))
            print("")
        elif result.reason == speechsdk.ResultReason.Canceled:
            cancellation_details = result.cancellation_details
            print("Speech synthesis canceled: {}".format(cancellation_details.reason))
            if cancellation_details.reason == speechsdk.CancellationReason.Error:
                print("Error details: {}".format(cancellation_details.error_details))

        #  将输出写到内存中
        url = upload_file_cos(file_type=COSFileType.VOICE, file_content=result.audio_data, file_extension='mp3', content_type=None)

        # 检查延迟
        # first byte latency	指示开始合成与接收第一个音频区块之间的时间延迟
        # finish latency	指示开始合成与接收全部合成音频之间的时间延迟。
        first_byte_latency = int(
            result.properties.get_property(speechsdk.PropertyId.SpeechServiceResponse_SynthesisFirstByteLatencyMs))
        finished_latency = int(
            result.properties.get_property(speechsdk.PropertyId.SpeechServiceResponse_SynthesisFinishLatencyMs))
        print("First byte latency: {}".format(first_byte_latency))
        print("Finished latency: {}".format(finished_latency))

        return url



'''
if __name__ == "__main__":
    # text_to_mp3("这是参数文本合成示例")
    # ssml_file_to_mp3()
    # text_to_mp3_costume_voice("这是定制发声人参数文本合成示例",3)


    # 测试函数模式生成ssml语音
    speaker = {'name': 'zh-CN-XiaoxiaoNeural'}
    style = {'style': 'sad', 'styledegree': '2'}
    text = "这是参数文本合成示例"
    prosody = {'rate': 'fast', 'volume': 'medium', 'pitch': 'low'}
    ssml_file_to_mp3_costume_voice(text, speaker, style, prosody)
'''