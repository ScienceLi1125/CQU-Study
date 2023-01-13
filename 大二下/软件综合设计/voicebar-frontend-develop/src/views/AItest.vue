<template>
	<!-- 顶部导航栏 -->
	<van-nav-bar fixed title="测试" left-arrow @click-left="onClickBack" />
	<div style="height:46px"></div>
	<div style="height: 20px; background-color: #f7f8fa;"></div>
	<!-- 图片上传区域 -->
	<van-config-provider :theme-vars="theme0">
		<van-uploader v-model="fileList" :max-count="1" :max-size="2048 * 1024" image-fit="scale-down"
			@oversize="onOversize" :preview-size="[225, 225]" :after-read="afterUploadImage" :before-delete="beforeDeleteImage"/>
	</van-config-provider>
	<!-- 开始测试按钮 -->
	<div style="height: 20px"></div>
	<div style="display: flex;">
		<div style="width: 35%;"></div>
		<div style="width: 30%;">
			<van-button @click="onClickTest" round type="primary" color="#1989FA" size="large" :loading="isLoading" loading-text="处理图片中">开始测试</van-button>
		</div>
		<div style="width: 35%;"></div>
	</div>
	<div style="height: 20px;"></div>
	<!-- 测试结果区 -->
	<van-cell-group inset>
		<van-config-provider :theme-vars="theme">
			<div style="font-weight: 900;">
				<van-cell title="测试结果" />
			</div>
		</van-config-provider>
		<div style="text-align: left;">
			<van-config-provider :theme-vars="themeVars">
				<van-cell title="性别" :value="gender" />
				<van-cell title="年龄" :value="age" />
				<van-cell title="颜值得分" :value="score" />
				<van-cell title="是否戴眼镜" :value="glass" />
				<van-cell title="表情" :value="emotion" />
			</van-config-provider>
		</div>
	</van-cell-group>
	<div style="height: 20px;"></div>
	<!-- 结果音频预览区 -->
	<Player v-if="testResult" theme="light" style="--vm-player-theme: #e86c8b;">
		<Audio>
			<source :data-src="testResult.mp3_url" type="audio/mp3" />
		</Audio>
		<DefaultUi noSettings />
	</Player>
	<!-- 分享按钮区 -->
	<div style="height: 20px;"></div>
	<div style="display: flex;justify-content: center;">
		<div style="width:30%;display: flex;justify-content: center;">
				<van-button @click="onClickShare" :disabled="!testResult" :loading="isLoading" round type="primary" icon="share-o" color="#1989FA" size="large" loading-text="处理图片中">
					分享
				</van-button>
		</div>
	</div>
	<div style="height: 20px;"></div>

	<!-- 图像裁剪遮罩层 -->
	<van-overlay :show="showCropperOverlay" :lock-scroll="false">
		<van-nav-bar title="图像裁剪" left-arrow @click-left="onClickCropperLeft" @click-right="onClickCropperConfirm">
			<template #right>
				<van-icon name="success" size="18" />
			</template>
		</van-nav-bar>
		<div class="cropper-wrapper">
			<vue-cropper :img="cropperImage" :canMove="false" outputType="png" autoCrop :autoCropWidth="150"
				:autoCropHeight="150" centerBox ref="cropper" class="avatar-cropper" />
		</div>
	</van-overlay>

	<!-- 分享弹框输入标题 -->
	<v-dialog v-model:show="showInputTitle" title="分享主题" close-on-click-overlay show-cancel-button @confirm="onConfirmShare" :before-close="validateTitle">
		<van-field
		v-model="title"
		placeholder="输入你的分享主题吧"
		maxlength="20"
		show-word-limit
		>
		</van-field>
	</v-dialog>

</template>

<script>
import { uploadFaceTestImage, publishTestResult } from "@/utils/api/face_test"
import { Player, Audio, DefaultUi } from '@vime/vue-next';
import { Dialog } from 'vant'

const theme0 = {
	uploaderIconColor: '#c9e2fa',
	uploaderUploadBackgroundColor: '#f1f6fa',
	uploaderIconSize: '30px',
};
const theme = {
	cellFontSize: '20px',
};
const themeVars = {
	cellFontSize: '18px',
	cellLineHeight: '30px',
};

export default {
	components: {
		Player,
		Audio,
		DefaultUi,
		'v-dialog': Dialog.Component, //vant3 bug
	},
	data() {
		return {
			fileList: [], //Uploader绑定上传文件预览
			showCropperOverlay: false, //是否显示裁剪遮罩层
			cropperImage: null, //裁剪组件图像来源
			testResult: null, //测试所得结果(服务器响应)
			isLoading: false, //是否正在测试
			title: "", //分享主题 标题输入绑定
			showInputTitle: false, //是否显示分享对话框
		}
	},
	computed: {
		theme0() { //暴露常量
			return theme0
		},
		theme() { //暴露常量
			return theme
		},
		themeVars() { //暴露常量
			return themeVars
		},
		gender() { //性别转换
			if (!this.testResult) {
				return ""
			}
			else {
				if (this.testResult.gender == 2) {
					return "男"
				}
				else {
					return "女"
				}
			}
		},
		age() {
			if (!this.testResult) {
				return ""
			}
			else {
				return this.testResult.age
			}
		},
		score() {
			if (!this.testResult) {
				return ""
			}
			else {
				return this.testResult.score
			}
		},
		glass() {
			if (!this.testResult) {
				return ""
			}
			else {
				if (this.testResult.glass) {
					return "戴眼镜"
				}
				else {
					return "不戴眼镜"
				}
			}
		},
		emotion() { //情绪转换
			if (!this.testResult) {
				return ""
			}
			switch (this.testResult.emotion) {
				case 'anger':
					return "愤怒"
				case 'disgust':
					return "厌恶"
				case 'fear':
					return "恐惧"
				case 'happiness':
					return "高兴"
				case 'neutral':
					return "中性"
				case 'sadness':
					return "伤心"
				case 'surprise':
					return "惊讶"
				case 'bigsmile':
					return "大笑"
				default:
					return "无效数据"
			}
		}
	},
	methods: {
		onClickBack() {
			this.$router.back()
		},
		onClickCropperLeft() { //放弃图像裁剪
			this.fileList = []
			this.showCropperOverlay = false
		},
		async onClickCropperConfirm() {
			this.$refs.cropper.getCropData(data => {
				// 更新fileList中的content,显示预览
				this.fileList[0].content = data
			})
			this.$refs.cropper.getCropBlob(data => {
				// 绑定blob,便于后续上传
				this.fileList[0].image_data = data
			})
			this.showCropperOverlay = false
		},
		onOversize() { //文件大小超标提示
			this.$toast.fail("文件大小不能超过2MB")
		},
		afterUploadImage(file) { //读入文件后进行裁剪
			this.showCropperOverlay = true
			this.cropperImage = window.URL.createObjectURL(file.file)
		},
		async onClickTest() { //点击开始测试按钮触发函数
			this.isLoading = true
			this.fileList[0].deletable = false //禁止删除
			try {
				const result = await uploadFaceTestImage(this.fileList[0].image_data)
				this.$toast.clear()
				this.testResult = result.data //获得测试结果
			} catch (error) {
				this.$toast.clear()
				if (!error.response.status) {
					this.$toast.fail("服务器没有响应或本地无网络连接")
				}
				else if (error.response.data === 500) {
					this.$toast.fail("服务器出现了一点问题")
				}
				else {
					this.$toast.fail(`人脸识别图片失败${JSON.stringify(error.response.data)}`)
				}
			}
			this.isLoading = false
			this.fileList[0].deletable = true
		},
		beforeDeleteImage() {
			//清空结果
			this.testResult = null
			return true
		},
		onClickShare() {
			this.showInputTitle = true
		},
		async onConfirmShare() {
			this.$toast.loading("上传文章中")
			try {
				await publishTestResult(this.testResult.result_id,this.title)
				this.$toast.clear()
				this.$toast.success("分享成功")
				this.$router.push({path:'/'})
			} catch (error) {
				this.$toast.clear()
				if (!error.response.status) {
					this.$toast.fail("服务器没有响应或本地无网络连接")
				}
				else if (error.response.data === 500) {
					this.$toast.fail("服务器出现了一点问题")
				}
				else {
					this.$toast.fail(`分享人脸识别结果失败${JSON.stringify(error.response.data)}`)
				}
			}
		},
        async validateTitle(action){ //标题输入校验
            if (action === "cancel"){
				this.title = ""
                return true
            }
            //校验 不能是空白
            if (this.title.trim() === "") {
                this.$toast.fail("标题不能为空")
                return false
            }
            return true
        },
	}
}

</script>

<style>
.cropper-wrapper {
	width: 90%;
	height: 90%;
	margin: 0 auto;
	z-index: 10;
}
</style>
