<template>
	<div class="article-container">
		<van-config-provider :theme-vars="themeVars">
			<van-swipe-cell>
				<van-cell class="article-cell" square :value="publish_time" :to="`/article/${articleInfo.id}`"
					style="font-weight:700;text-align: left;margin-bottom: 10px;">
					<template #title>
						<div class="article-title-container">
							<span class="article-title">{{articleInfo.title}}</span>
						</div>
					</template>
				</van-cell>
				<template #right>
					<van-button @click="onClickDelete" square type="danger" text="删除" style="height: 100%;" />
				</template>
			</van-swipe-cell>
		</van-config-provider>
	</div>
</template>

<script>
import {parseTime} from "@/utils/timeparse"
import {deleteArticle} from "@/utils/api/articles"

const themeVars = {
	cellLineHeight: '50px',
	cellFontSize: '18px',
}

export default {
	name: 'MyArticleCard',
	emits: ['deleteArticle'],
    props: ['articleInfo'],
    computed: {
        themeVars() {
            return themeVars
        },
        publish_time() {
            return parseTime(this.articleInfo.pub_date)
        },
	},
	methods: {
		onClickDelete() {
			deleteArticle(this.articleInfo.id)
			this.$emit('deleteArticle',this.articleInfo.id)
		}
	}
}
</script>

<style scoped lang="scss">

.article-cell {
	:deep(.van-cell__title) {
		min-width: 70%;
		max-width: 75%;
	}
}

.article-title-container {
	overflow: hidden;
	.article-title {
		display: block;
		text-align: left;
		white-space:nowrap;
		overflow: hidden;
		text-overflow:ellipsis;
	}
}

</style>