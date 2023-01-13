<template>
	<van-nav-bar fixed left-arrow @click-left="onClickNavLeft" left-text="返回" title="ta的文章" />

    <div style="height:46px;"></div>

    <!-- 若登录用户为管理员则使用滑动删除组件 -->
    <van-list v-if="!is_admin" v-model:loading="loading" :finished="finished" finished-text="没有更多了" @load="onLoadArticles">
        <article-card v-for="item in articleList" :key="item.id" :articleInfo="item" />
    </van-list>

    <van-list v-else v-model:loading="loading" :finished="finished" finished-text="没有更多了" @load="onLoadArticles">
        <admin-article-card v-for="item in articleList" :key="item.id" :articleInfo="item" @deleteArticle="onDeleteArticle" />
    </van-list>

</template>

<script>
import OthersArticleCard from "@/components/OthersArticleCard.vue"
import MyArticleCard from "@/components/MyArticleCard.vue"
import {getUserArticles} from "@/utils/api/users"
import {getSelfProfile} from "@/utils/api/me"
import { retrieveUserProfile, storeUserProfile } from "@/utils/storage"

export default {
    data() {
        return {
            loading: false, //控制List组件是否处于加载状态
            finished: false, //控制List组件是否没有更多数据可加载
            loadingPage: 1, //记忆当前已加载到的页数
            articleList: [], //存放List加载到信息的数组
            selfProfile: null, //当前登录用户状态
        }
    },
    components: {
        'article-card':OthersArticleCard,
        'admin-article-card':MyArticleCard,
    },
    computed: {
        user_id() {
            return this.$route.params.user_id
        },
        is_admin() {
            return this.selfProfile?.is_admin
        }
    },
	methods: {
		onClickNavLeft(){
			this.$router.back()
		},
        async onLoadArticles() { //List需要加载时调用函数
            const data = await getUserArticles(this.user_id,this.loadingPage)
            this.loadingPage++
            this.articleList.push(...data)
            if (!data.length) {
                this.finished = true
            }
            this.loading = false
        },
        async loadSelfProfile() { //获取当前登录用户状态
            const result = await getSelfProfile()
            this.selfProfile = result.data
            storeUserProfile(result.data)
        },
        onDeleteArticle(article_id) { //接受滑动删除组件发来的信号,及时响应
            const result = this.articleList.filter(article => article.id != article_id)
            this.articleList = result
        }
	},
    mounted() {
        this.selfProfile = retrieveUserProfile() //载入本地缓存
        this.loadSelfProfile()
    }
}
</script>

<style>
</style>