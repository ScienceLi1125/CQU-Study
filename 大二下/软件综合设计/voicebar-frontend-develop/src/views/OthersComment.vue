<template>
    <van-nav-bar fixed title="ta的评论" left-arrow @click-left="onClickNavLeft"/>

    <div style="height:46px"></div>

    <!-- 若登录用户为管理员则使用滑动删除组件 -->
    <van-list v-if="!is_admin" v-model:loading="loading" :finished="finished" finished-text="没有更多了" @load="onLoadComments">
        <comment-card v-for="item in commentList" :key="item.id" :commentInfo="item" />
    </van-list>

    <van-list v-else v-model:loading="loading" :finished="finished" finished-text="没有更多了" @load="onLoadComments">
        <admin-comment-card v-for="item in commentList" :key="item.id" :commentInfo="item" @deleteComment="onDeleteComment" />
    </van-list>

</template>

<script>
import OthersCommentCard from '@/components/OthersCommentCard.vue';
import {getUserComments} from '@/utils/api/users'
import {getSelfProfile} from "@/utils/api/me"
import { retrieveUserProfile, storeUserProfile } from "@/utils/storage"
import MyCommentCard from '@/components/MyCommentCard.vue';

export default{
    name:'OthersComment',
    components: {
        'comment-card':OthersCommentCard,
        'admin-comment-card':MyCommentCard,
    },
    data() {
        return {
            loading: false, //控制List组件是否处于加载状态
            finished: false, //控制List组件是否没有更多数据可加载
            loadingPage: 1, //记忆当前已加载到的页数
            commentList: [], //存放List加载到信息的数组
            selfProfile: null, //当前登录用户状态
        }
    },
    computed: {
        user_id() {
            return this.$route.params.user_id
        },
        is_admin() {
            return this.selfProfile?.is_admin
        }
    },
    methods:{
        onClickNavLeft(){
            this.$router.back()
        },
        async onLoadComments() { //List需要加载时调用函数
            const data = await getUserComments(this.user_id,this.loadingPage)
            this.loadingPage++
            this.commentList.push(...data)
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
		onDeleteComment(comment_id) { //接受滑动删除组件发来的信号,及时响应
			const result = this.commentList.filter(comment => comment.id != comment_id)
			this.commentList = result
		}
    },
    mounted() {
        this.selfProfile = retrieveUserProfile()
        this.loadSelfProfile()
    }
}
    
</script>

<style>
</style>