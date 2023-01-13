<template>
    <van-skeleton title avatar :row="3" :loading="isLoading">
        <van-cell-group>
            <author-card @clickHead="onClickHead" class="comment-author-card" :user_id="author.id" :nickname="author.nickname" :avatar_url="author.avatar_url" :publish_time="publish_time" :disableBorder="true" :ip_loc="ip" :floor_num="floor_num" :is_admin="author.is_admin"></author-card>

            <div style="height:10px"></div>

            <!-- 评论内容 -->
            <div class="comment-content">
                {{comment_content}}
            </div>

            <div style="height:10px"></div>

        </van-cell-group>
    </van-skeleton>
</template>

<script>

import ArticleUserCard from "./ArticleUserCard.vue"
import {getUserProfile} from "@/utils/api/users"
import {parseTime} from "@/utils/timeparse"

export default {
    name: 'ArticleCommentCard',
    emits: ['clickHead'],
    props: ['commentInfo'],
    components: {
        'author-card': ArticleUserCard,
    },
    data() {
        return {
            author: null,
            isLoading: true,
        }
    },
    computed: {
		floor_num() {
			const floor_res = this.commentInfo.index + "楼"
			return floor_res
		},
		ip() {
			return this.commentInfo.ip_loc
		},
        comment_content() {
            return this.commentInfo.post
        },
        publish_time() {
            return parseTime(this.commentInfo.pub_date)
        },
    },
    methods: {
        async startLoad() {
            this.author = await await getUserProfile(this.commentInfo.user)
            this.isLoading = false
        },
        onClickHead(user_id) {
            this.$emit('clickHead',user_id)
        }
    },
    mounted() {
        this.startLoad()
    },
}

</script>

<style lang="scss" scoped>

.comment-author-card {
    padding-left: 4%;
    padding-top: 5px;
}

.comment-content {
    white-space: pre-line;
    word-break: break-word;
    margin: 0;
    text-align: start;
    padding-left: 4%;
    padding-right: 4%;
}

</style>