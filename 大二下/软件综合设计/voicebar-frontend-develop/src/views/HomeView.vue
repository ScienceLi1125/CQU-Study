<template>
  <div class="home">
    <!-- 顶部导航栏 -->
    <van-nav-bar fixed title="所有文章" />
    <div style="height:46px"></div>
    <!-- 下拉刷新 -->
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
import {getAllArticles} from '@/utils/api/articles'
import ArticleSummaryCard from '@/components/ArticleSummaryCard'

export default {
  name: 'HomeView',
  components: {
    ArticleSummaryCard
},
  data() {
    return {
      PullRefreshloading: false, //指示下拉刷新状态
      loading: false, //指示List加载状态
      finished: false, //指示List是否还有数据可加载
      articleInfoList: [], //List绑定信息数组
      loadingPage: 1, //当前加载到的页数
    }
  },
  methods: {
    async onLoadArticles() { //触发List加载的函数
      const data = await getAllArticles(this.loadingPage)
      this.articleInfoList.push(...data)
      this.loading = false
      this.loadingPage = this.loadingPage + 1
      if (!data.length) {
          this.finished = true
      }
    },
    onClickArticleContent(article_id) { //点击进入文章详情
      this.$router.push({path:`/article/${article_id}`})
    },
    onClickArticleHead(user_id) { //点击进入文章作者个人信息页
      this.$router.push({path:`/user/${user_id}`})
    },
    onRefresh() { //下拉刷新触发
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
