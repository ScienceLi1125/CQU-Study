<template>
    <!-- 顶部导航栏复用 -->
    <van-nav-bar v-if="!isAliasForMe" fixed title="ta的关注" left-arrow @click-left="onClickBack" />
    <van-nav-bar v-else fixed title="我的关注" left-arrow @click-left="onClickBack" />
    <div style="height:46px"></div>

    <van-list v-model:loading="loading" :finished="finished" finished-text="没有更多了" @load="onLoadFollowings">
        <fan-card v-for="item in followingList" :key="item.id" :userInfo="item" />
    </van-list>

</template>

<script>
import {getUserFollowings} from "@/utils/api/users"
import {getSelfFollowings} from "@/utils/api/me"
import FollowersFansCard from "@/components/FollowersFansCard.vue"

export default {
    name: 'FollowersView',
    components: {
        'fan-card': FollowersFansCard,
    },
    computed: {
        user_id() {
            return this.$route.params.user_id
        },
        isAliasForMe() { //复用页面,当检测到user_id为me时应显示自己的关注
            return this.$route.params.user_id === "me"
        },
    },
    data() {
        return {
            loading: false, //表示List的加载状态
            finished: false, //表示List是否还有更多数据可加载
            loadingPage: 1, //当前已加载页数
            followingList: [], //List绑定信息
        }
    },
    methods: {
        onClickBack() {
            this.$router.back()
        },
        async onLoadFollowings() {
            let data
            if (!this.isAliasForMe) { //根据是看自己的还是看别人的有不同的网络逻辑
                data = await getUserFollowings(this.user_id, this.loadingPage)
            }
            else {
                data = await getSelfFollowings(this.loadingPage)
            }
            this.followingList.push(...data)
            this.loading = false
            this.loadingPage = this.loadingPage + 1
            if (!data.length) {
                this.finished = true
            }
        }
    },
};
</script>

<style>
</style>