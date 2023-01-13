<template>
    <van-nav-bar fixed title="我的评论" left-arrow @click-left="onClickNavLeft"/>

    <div style="height:46px"></div>

    <van-list v-model:loading="loading" :finished="finished" finished-text="没有更多了" @load="onLoadComments">
        <comment-card v-for="item in commentList" :key="item.id" :commentInfo="item" @deleteComment="onDeleteComment" />
    </van-list>

</template>

<script>
import MyCommentCard from '@/components/MyCommentCard.vue'
import {getUserComments} from '@/utils/api/users'
import { retrieveUserProfile } from '@/utils/storage'

export default{
    name:'MyComment',
    components: {
        'comment-card':MyCommentCard,
    },
    data() {
        return {
            loading: false, //List组件加载状态
            finished: false, //List组件是否还有更多数据可取
            loadingPage: 1, //当前加载到的页数
            commentList: [], //List组件绑定的展示信息
			userProfile: null, //当前登录用户信息,主要用于获取用户ID
        }
    },
    computed: {
    },
    methods:{
        onClickNavLeft(){
            this.$router.back()
        },
        async onLoadComments() {
            const data = await getUserComments(this.userProfile.id,this.loadingPage)
            this.loadingPage++
            this.commentList.push(...data)
            if (!data.length) {
                this.finished = true
            }
            this.loading = false
        },
		onDeleteComment(comment_id) { //响应滑动删除组件的删除事件
			const result = this.commentList.filter(comment => comment.id != comment_id)
			this.commentList = result
		}
    },
	mounted() {
		this.userProfile = retrieveUserProfile()
	}
}
    
</script>

<style>
</style>