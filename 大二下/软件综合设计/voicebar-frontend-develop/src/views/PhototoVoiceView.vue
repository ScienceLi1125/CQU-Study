<template>
	<van-nav-bar title="图片语音" fixed />

	<div style="height:46px"></div>
	
	<div>
		<!-- A梦锐评图片 -->
		<img src="../picture/AmengT.png" width="170px" height="120px"/>
	</div>
	<div style="display: flex;height: 100px;">
        <div style="width:15%;"></div>
		<div style="width:30%;">
			<!-- A梦动图 -->
			<img src="../picture/Ameng.gif" width="120px" height="120px" />
		</div>
        <div style="width:10%;"></div>
		<div style="width:30%;">
			<!-- 吴京图片 -->
			<img src="../picture/wj.jpeg" width="120px" height="120px"/>
		</div>
        <div style="width:15%;"></div>
	</div>
	<div style="height: 30px;"></div>
	<van-cell-group inset>
		<van-config-provider :theme-vars="theme">
			<div style="font-weight: 900;">
				<van-cell title="示例测试结果"/>
			</div>
		</van-config-provider>
		<div style="text-align: left;">
				<van-config-provider :theme-vars="themeVars">
					<van-cell title="性别" value="男"/>
					<van-cell title="年龄" value="48" />
					<van-cell title="颜值得分" value="72"/>
					<van-cell title="是否戴眼镜" value="不戴眼镜"/>
					<van-cell title="表情" value="中性" />
				</van-config-provider>
		</div>
	</van-cell-group>
	<div style="height: 20px;"></div>
	<div style="display: flex;">
		<div style="width: 10%;"></div>
		<div style="width: 30%;">
			<!-- 语音播报按钮 -->
			<van-button round :disabled="playing" type="primary" icon="volume-o" color="#1989FA" size="large" @click="playExample">语音播报</van-button>
		</div>	
		<div style="width: 20%;"></div>
		<div style="width: 30%;">	
			<!-- 跳转至评测页面按钮 -->
			<van-button round type="primary" icon="guide-o" color="#1989FA" size="large" to="/phototovoice/aitest">开始测评</van-button>
		</div>
		<div style="width: 10%;"></div>
	</div>

	<div style="height: 70px"></div>

</template>

<script>
//自定义主题
const theme = {
	cellFontSize:'20px',
}
const themeVars = {
	cellFontSize:'18px',
	cellLineHeight: '30px',
}

export default{
	name:'PhototoVoiceView',
	data() {
		return {
			playing: false, //示例音频是否在播放
			audio: null, //音频播放对象
		}
	},
	computed: { //暴露自定义主题
		theme() {
			return theme
		},
		themeVars() {
			return themeVars
		}
	},
	methods: {
		async playExample () {
			//不允许重复播放
			this.playing = true
			this.audio = new Audio("https://voicebar-1251996605.cos.ap-shanghai.myqcloud.com/voice/0eb798ef-1753-4f18-872d-9a90c2b4f837.mp3");
			this.audio.onended = () => {this.playing = false;}
			await this.audio.play();
		},
		onClickLeft() {history.back()}
	},
	unmounted() {
		//离开时停止播放
		if (this.audio) {
			this.audio.pause()
			this.audio = null
		}
	}
};	
</script>

<style>
</style>
