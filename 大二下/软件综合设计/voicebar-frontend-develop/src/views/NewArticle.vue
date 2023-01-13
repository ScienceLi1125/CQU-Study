<template>
	<!-- 顶部导航栏 -->
	<van-nav-bar
		title="发布文章"
		right-text="发布"
		left-arrow
		fixed
		@click-left="onClickBack"
		@click-right="onClickPublish"
	/>

	<!-- 导航栏为fixed时需要将元素往下挤 -->
	<div style="height:46px"></div>

	<div style="height: 10px;" />

	<!-- 标题输入区域 -->
	<van-cell-group class="article-title-cellgroup" >
		<van-field v-model="article_title" placeholder="标题" />
	</van-cell-group>

	<div style="height: 10px;" />

	<!-- 正文输入组件 -->
	<WriteArticleRich @change="onChange"/>
	
	<!-- 图片上传区域 -->
	<div class="image-uploaders-area">
		<van-config-provider :theme-vars="themeVars">
			<van-uploader
			v-model="imageList"
			multiple 
			:preview-size="0.3 * windowWidth"
			:after-read="afterReadUpload"
			max-count="9">
			</van-uploader>
		</van-config-provider>
	</div>

	<!-- 语音生成选项区 -->
    <van-config-provider :theme-vars="themeVars1">
        <van-cell center class="title-info-container" value="文本朗读" icon='play-circle-o'>
            <template #right-icon>
                <van-switch v-model="enableRead" size="24" active-color="#1989FA"/>
            </template>
        </van-cell>
		<div v-if="enableRead" style="text-align: left;">
			<van-cell center class="title-info-container voice-option-cell" icon="fire-o" is-link clickable title="语音选项" :value="current_speaker_select_text" @click="onClickVoiceOption"/>
			<van-popup :show="showVoiceOptionPopup" close-on-click-overlay @close="onCloseVoiceOption" round position="bottom" :style="{ height: '40%' }">
				<van-tree-select
				v-model:active-id="activeStyleId"
				v-model:main-active-index="activeSpeakerId"
				:items="voiceOptionItems"
				/>
			</van-popup>
		</div>	
    </van-config-provider>
	<div style="height: 10px;"></div>
</template>

<script>
	
	import WriteArticleRich from '@/components/WriteArticleRich.vue';
	import { storeVoiceSpeaker, retrieveVoiceSpeaker, storeVoiceSpeakerStyle, retrieveVoiceSpeakerStyle, storeVoiceOptions, retrieveVoiceOptions ,storeEnableVoice ,retrieveEnableVoice} from '@/utils/storage';
	import {uploadArticleImage, publishArticle, getVoiceOptions} from '@/utils/api/articles'

    const themeVars = {
        uploaderDeleteIconSize: '20px',
    }
	const themeVars1 = {
		cellIconSize: '20px',
	}
	export default {
		data() {
			return {
				enableRead: false,
				windowWidth: document.documentElement.clientWidth,
				article_content: '', //绑定当前正文输入框中的文字
				article_title: '', //绑定当前标题输入框中的文字
				imageList: [], //绑定Uploader上传图片List
				uploadingCount: 0, //记录当前正在上传的图片个数,不为0不允许发布
				voice_options: null, //从服务器取得的语音选项
				showVoiceOptionPopup: false, //控制是否显示语音选择Popup
				activeStyleId: 0, //当前说话风格ID 默认为0
				activeSpeakerId: 0, //当前说话人ID 默认为0
			}
		},
		components: {
			WriteArticleRich
		},
		computed: {
			themeVars() { //暴露常量
				return themeVars
			},
			themeVars1() {
				return themeVars1
			},
			publishContent() {
				//生成图片ID LIST
				const imageIDList = []
				this.imageList.forEach(image => {
					if (image.status === "done") {
						imageIDList.push(image.article_image_id)
					}
				})
				return {
					post: this.article_content,
					title: this.article_title,
					images: imageIDList,
					enableVoice: this.enableRead,
					speakerId: this.activeSpeakerId,
					styleId: this.activeStyleId,
				}
			},
			voiceOptionItems() {
				//将服务器给的响应转换为TreeSelect组件使用的形式
				if (!this.voice_options) {
					return null
				}
				const result = []
				this.voice_options.forEach(speaker_option => {
					const children_style = []
					let id = 0
					speaker_option.styles.forEach(style => {
						children_style.push({
							text:style,
							id:id,
						})
						id++
					})
					const item = {
						text: speaker_option.name,
						children: children_style,
					}
					result.push(item)
				})
				return result
			},
			current_speaker_select_text() {
				//根据用户选择生成当前语音选项展示文本
				if (!this.voice_options) {
					return ""
				}
				const speaker_name = this.voice_options[this.activeSpeakerId].name
				const style_name = this.voice_options[this.activeSpeakerId].styles[this.activeStyleId]
				return `${speaker_name}>${style_name}`
			}
		},
		methods: {
			onClickBack() {history.back()},
			async onClickPublish() {
				if (this.uploadingCount !== 0) {
					this.$toast.fail("图片仍在上传中")
					return
				}
				else {
					this.$toast.loading("上传文章中")
					try {
						await publishArticle(this.publishContent)
						this.$toast.clear()
						this.$toast.success("发布成功")
					} catch (error) {
						this.$toast.clear()
						this.$toast.fail(`上传文章失败\n${JSON.stringify(error.response.data)}`)
					}
					this.$router.push({path:'/'})
				}
			},
			//绑定正文输入框内容
			onChange(text) {this.article_content = text},
			//关闭TreeSelect时自动保存
			onCloseVoiceOption() {
				this.showVoiceOptionPopup = false
				if (this.activeStyleId >= this.voice_options[this.activeSpeakerId].styles.length) { //ID超出范围没有选择自动为第一项
					this.activeStyleId = 0
				}
				storeVoiceSpeaker(this.activeSpeakerId)
				storeVoiceSpeakerStyle(this.activeStyleId)
			},
			afterReadUpload(images) { //Uploader读入本地图片后开始向服务器上传,节省用户发帖等待时间
				let imageList
				if (!(images instanceof Array)) {
					imageList = [images]
				}
				else {
					imageList = images
				}
				imageList.forEach(async (image) => {
					this.uploadingCount += 1
					image.status='uploading'
					try {
						const result = await uploadArticleImage(image.file)
						image.article_image_id = result.data.id
						image.status='done'
					} catch(error) {
						image.status='failed'
						if (error.response.status === 500) {
							this.$toast.fail("服务器出现了一点问题")
						} else {
							this.$toast.fail(`上传图片失败\n${JSON.stringify(error.response.data)}`)
						}
					}
					this.uploadingCount -= 1
				})
			},
			onClickVoiceOption() {
				this.showVoiceOptionPopup = true
			},
			async loadNetworkVoiceOptions() { //从服务器拉取最新可用的语音选项
				const data = await getVoiceOptions()
				this.voice_options = data
				storeVoiceOptions(data)
			},
			retrieveOptions() { //读取本地缓存中的配置
				if (retrieveVoiceOptions()) {
					this.voice_options = retrieveVoiceOptions()
				}
				if (retrieveVoiceSpeaker()) {
					this.activeSpeakerId = retrieveVoiceSpeaker()
				}
				if (retrieveVoiceSpeakerStyle()) {
					this.activeStyleId = retrieveVoiceSpeakerStyle()
				}
				if (retrieveEnableVoice()) {
					this.enableRead = retrieveEnableVoice()
				}
			}
		},
		mounted() {
			this.retrieveOptions()
			this.loadNetworkVoiceOptions()
		},
		unmounted() { //离开页面时保存是否启用语音朗读的配置
			storeEnableVoice(this.enableRead)
		},
	};

</script>

<style lang="scss" scoped>

.image-uploaders-area {
	padding-left: 3%;
	display: flex;
	margin: 0 auto;
	:deep(.van-uploader__wrapper) {
		.van-uploader__upload {
			background-color: #f0f0f0; //与背景颜色区分
		}
	}
}
.title-info-container{
    //padding-top: 5px;
    //padding-bottom: 0px;
    height: 50px;
    font-size: 18px;
}

.voice-option-cell {
	:deep(.van-cell__value) {
		min-width: 65%; //调宽展示语音选项cell的右侧文本区域
	}
}

</style>
