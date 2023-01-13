<template>
  <!-- 与主页相似,但是只显示用户关注的作者发布的帖子,只有网络逻辑有变化 -->
  <div>
    <van-nav-bar title="关注" fixed />
    <div style="height:46px"></div>
  <van-pull-refresh v-model="PullRefreshloading" @refresh="onRefresh">
    <van-list
      v-model:loading="loading"
      :finished="finished"
      finished-text="没有更多了"
      @load="onLoadArticles"
    >
      <article-summary-card v-for="item in articleInfoList" :key="item.id" :articleInfo="item" :enableGap="true" @clickContent="onClickArticleContent" @clickHead="onClickArticleHead" />
    </van-list>	
  </van-pull-refresh>
  </div>
</template>

<script>
// @ is an alias to /src
import {getFollowedArticle} from '@/utils/api/articles'
import ArticleSummaryCard from '@/components/ArticleSummaryCard'

export default {
  name: 'FollowView',
  components: {
    ArticleSummaryCard
},
	data() {
		return {
			loading: false,
			finished: false,
			articleInfoList: [],
			loadingPage: 1,
      PullRefreshloading: false,
		}
	},
  methods: {
    async onLoadArticles() {
      const data = await getFollowedArticle(this.loadingPage)
      this.articleInfoList.push(...data)
      this.loading = false
      this.loadingPage = this.loadingPage + 1
      if (!data.length) {
        this.finished = true
      }
    },
    onClickArticleContent(article_id) {
      this.$router.push({path:`/article/${article_id}`})
    },
    onClickArticleHead(user_id) {
      this.$router.push({path:`/user/${user_id}`})
    },
    onRefresh() {
      this.articleInfoList = []
      this.loadingPage = 1
      this.finished = false
      this.loading = true
      this.PullRefreshloading = false
      this.onLoadArticles()
    }
  },
}
</script>
