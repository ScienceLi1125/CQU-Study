<template>
	<van-skeleton title avatar :row="3" :loading="isLoading">
		<van-config-provider :theme-vars="themeVars1" style="text-align: left;margin-bottom: -10px;">
			<van-cell class="comment-cell" :value="publish_time" :to="`/article/${commentInfo.reply_to}`">
				<template #title>
					<div class="comment-title-container">
						<span class="comment-title">{{ articleInfo.title }}</span>
					</div>
				</template>
			</van-cell>
		</van-config-provider>
		<van-config-provider :theme-vars="themeVars">
			<div style="font-weight: 550;margin-top: -15px;margin-bottom: 10px;">
				<van-cell :value="commentInfo.post" :to="`/article/${commentInfo.reply_to}`" />
			</div>
		</van-config-provider>
	</van-skeleton>
</template>

<script>
import { getArticleDetail } from "@/utils/api/articles"
import { parseTime } from "@/utils/timeparse"

const themeVars = {
	cellFontSize: "18px",
	cellLineHeight: "20px",
}
const themeVars1 = {
	cellFontSize: "15px",
	cellLineHeight: "30px",
}

export default {
	name: 'OthersCommentCard',
	props: ["commentInfo"],
	data() {
		return {
			isLoading: true,
			articleInfo: null,
		}
	},
	computed: {
		themeVars() {
			return themeVars
		},
		themeVars1() {
			return themeVars1
		},
		publish_time() {
			return parseTime(this.commentInfo.pub_date)
		}
	},
	methods: {
		async loadArticleInfo() {
			this.articleInfo = await getArticleDetail(this.commentInfo.reply_to)
		}
	},
	mounted() {
		this.loadArticleInfo().then(() => { this.isLoading = false })
	}
}
</script>

<style scoped lang="scss">
.comment-cell {
	:deep(.van-cell__title) {
		min-width: 75%;
	}
}

.comment-title-container {
	overflow: hidden;

	.comment-title {
		display: block;
		white-space: nowrap;
		overflow: hidden;
		text-overflow: ellipsis;
	}
}
</style>