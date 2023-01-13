<template>
    <!-- 顶部导航栏复用 -->
    <van-nav-bar v-if="!isAliasForMe" fixed title="ta的粉丝" left-arrow @click-left="onClickBack" />
    <van-nav-bar v-else fixed title="我的粉丝" left-arrow @click-left="onClickBack" />
    <div style="height:46px"></div>

    <van-list v-model:loading="loading" :finished="finished" finished-text="没有更多了" @load="onLoadFollowers">
        <fan-card v-for="item in followerList" :key="item.id" :userInfo="item" />
    </van-list>


</template>
<script>
import FollowersFansCard from "@/components/FollowersFansCard.vue"
import { getUserFollowers } from "@/utils/api/users"
import { getSelfFollowers } from "@/utils/api/me"

export default {
    name: 'FollowersView',
    components: {
        'fan-card': FollowersFansCard,
    },
    computed: {
        user_id() {
            return this.$route.params.user_id
        },
        isAliasForMe() { //复用页面
            return this.$route.params.user_id === "me"
        },
    },
    data() {
        return {
            loading: false,
            finished: false,
            loadingPage: 1,
            followerList: [],
        }
    },
    methods: {
        onClickBack() {
            this.$router.back()
        },
        async onLoadFollowers() {
            let data
            if (!this.isAliasForMe) { //看自己的与看别人的有不同的网络逻辑
                data = await getUserFollowers(this.user_id, this.loadingPage)
            }
            else {
                data = await getSelfFollowers(this.loadingPage)
            }
            this.followerList.push(...data)
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