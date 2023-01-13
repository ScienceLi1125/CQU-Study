<template>
    <van-nav-bar fixed left-arrow @click-left="onClickNavLeft" title="我的文章" />

    <div style="height:46px;"></div>

    <van-list v-model:loading="loading" :finished="finished" finished-text="没有更多了" @load="onLoadArticles">
        <article-card v-for="item in articleList" :key="item.id" :articleInfo="item" @deleteArticle="onDeleteArticle" />
    </van-list>

</template>

<script>
import MyArticleCard from "@/components/MyArticleCard.vue"
import { getUserArticles } from "@/utils/api/users"
import { retrieveUserProfile } from "@/utils/storage"

//与MyArticle类似的逻辑

const themeVars = {
    cellLineHeight: '50px',
    cellFontSize: '18px',
}

export default {
    data() {
        return {
            loading: false,
            finished: false,
            loadingPage: 1,
            articleList: [],
            userProfile: null,
        }
    },
    components: {
        'article-card': MyArticleCard
    },
    computed: {
        themeVars() {
            return themeVars
        }
    },
    methods: {
        onClickNavLeft() {
            this.$router.back()
        },
        async onLoadArticles() {
            const data = await getUserArticles(this.userProfile.id, this.loadingPage)
            this.loadingPage++
            this.articleList.push(...data)
            if (!data.length) {
                this.finished = true
            }
            this.loading = false
        },
        onDeleteArticle(article_id) {
            const result = this.articleList.filter(article => article.id != article_id)
            this.articleList = result
        }
    },
    mounted() {
        this.userProfile = retrieveUserProfile()
    }
}
</script>

<style>
</style>