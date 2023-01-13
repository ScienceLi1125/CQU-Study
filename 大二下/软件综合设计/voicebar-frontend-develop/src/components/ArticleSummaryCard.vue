<template>
    <van-skeleton title avatar :row="3" :loading="isLoading">
        <van-cell-group :border="false">
            <author-card class="article-author-card" @clickHead="onClickHead" :user_id="author.id"
                :nickname="author.nickname" :avatar_url="author.avatar_url" :publish_time="publish_time" :is_admin="author.is_admin">
            </author-card>

            <!-- 标题区 -->

            <div class="article-title" @click="onClickContent">{{ article_title }}</div>

            <vue-clamp class="article-content" :max-lines="5" @click="onClickContent">
                <template #after=scope>
                    <a href="javascript:void(0)" v-if="scope.clamped">展开</a>
                </template>
                {{ article_content }}
            </vue-clamp>

            <div v-if="imageList.length" style="height:10px"></div> <!-- 需要显示图片时 预留一点空间 -->

            <div v-if="imageList.length === 1" class="article-image-1 image-common">
                <!-- 只有一张图片 -->
                <van-image lazy-load :width="oneImageWidth" :height="oneImageHeight" fit="cover" :src="imageList[0]"
                    @click="showImagePreview(0)" @load="adjustImage" />
            </div>

            <div v-else-if="imageList.length === 2" class="article-image-2 image-common">
                <!-- 只有两张图片 -->
                <van-row gutter="5">
                    <van-col span="12">
                        <van-image lazy-load fit="cover" :height="0.46 * windowWidth" :src="imageList[0]"
                            @click="showImagePreview(0)" />
                    </van-col>
                    <van-col span="12">
                        <van-image lazy-load fit="cover" :height="0.46 * windowWidth" :src="imageList[1]"
                            @click="showImagePreview(1)" />
                    </van-col>
                </van-row>
            </div>

            <div v-else-if="imageList.length === 3" class="article-image-3 image-common">
                <!-- 只有三张图片 -->
                <van-row gutter="5">
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[0]"
                            @click="showImagePreview(0)" />
                    </van-col>
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[1]"
                            @click="showImagePreview(1)" />
                    </van-col>
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[2]"
                            @click="showImagePreview(2)" />
                    </van-col>
                </van-row>
            </div>

            <div v-else-if="imageList.length === 4" class="article-image-4 image-common">
                <!-- 只有四张图片 -->
                <van-row gutter="5">
                    <van-col span="12">
                        <van-image lazy-load fit="cover" :height="0.47 * windowWidth" :src="imageList[0]"
                            @click="showImagePreview(0)" />
                    </van-col>
                    <van-col span="12">
                        <van-image lazy-load fit="cover" :height="0.47 * windowWidth" :src="imageList[1]"
                            @click="showImagePreview(1)" />
                    </van-col>
                </van-row>
                <van-row gutter="5">
                    <van-col span="12">
                        <van-image lazy-load fit="cover" :height="0.47 * windowWidth" :src="imageList[2]"
                            @click="showImagePreview(2)" />
                    </van-col>
                    <van-col span="12">
                        <van-image lazy-load fit="cover" :height="0.47 * windowWidth" :src="imageList[3]"
                            @click="showImagePreview(3)" />
                    </van-col>
                </van-row>
            </div>

            <div v-else-if="imageList.length === 5 || imageList.length === 6" class="article-image-5_6 image-common">
                <!-- 只有5~6张图片 -->
                <van-row gutter="5">
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[0]"
                            @click="showImagePreview(0)" />
                    </van-col>
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[1]"
                            @click="showImagePreview(1)" />
                    </van-col>
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[2]"
                            @click="showImagePreview(2)" />
                    </van-col>
                </van-row>
                <van-row gutter="5">
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[3]"
                            @click="showImagePreview(3)" />
                    </van-col>
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[4]"
                            @click="showImagePreview(4)" />
                    </van-col>
                    <van-col v-if="imageList.length === 6" span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[5]"
                            @click="showImagePreview(5)" />
                    </van-col>
                </van-row>
            </div>

            <div v-else-if="imageList.length >= 7" class="article-image-7_8_9 image-common">
                <!-- 只有7~9张图片 -->
                <van-row gutter="5">
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[0]"
                            @click="showImagePreview(0)" />
                    </van-col>
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[1]"
                            @click="showImagePreview(1)" />
                    </van-col>
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[2]"
                            @click="showImagePreview(2)" />
                    </van-col>
                </van-row>
                <van-row gutter="5">
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[3]"
                            @click="showImagePreview(3)" />
                    </van-col>
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[4]"
                            @click="showImagePreview(4)" />
                    </van-col>
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[5]"
                            @click="showImagePreview(5)" />
                    </van-col>
                </van-row>
                <van-row gutter="5">
                    <van-col span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[6]"
                            @click="showImagePreview(6)" />
                    </van-col>
                    <van-col v-if="imageList.length >= 8" span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[7]"
                            @click="showImagePreview(7)" />
                    </van-col>
                    <van-col v-if="imageList.length === 9" span="8">
                        <van-image lazy-load fit="cover" :height="0.3 * windowWidth" :width="0.3 * windowWidth" :src="imageList[8]"
                            @click="showImagePreview(8)" />
                    </van-col>
                </van-row>
            </div>

            <van-divider class="article-action-divider" /> <!-- 分割线 -->

            <div class="article-action-container">
                <div class="article-action-common">
                    <van-icon class="article-action-icon" size="25" name="chat-o" @click="onClickContent" />
                    <div v-if="commentCount" class="article-action-number">{{ commentCount }}</div>
                    <div v-else class="article-action-empty">&ensp;</div>
                </div>
                <div class="article-action-common">
                    <van-icon v-if="!isLiked" class="article-action-icon" size="25" name="good-job-o"
                        @click="onClickLike" />
                    <van-icon v-else class="article-action-icon" color="#FB7299" size="25" name="good-job"
                        @click="onClickCancelLike" />
                    <div v-if="likedCount" class="article-action-number">{{ likedCount }}</div>
                    <div v-else class="article-action-empty">&ensp;</div>
                </div>
            </div>
        </van-cell-group>
    </van-skeleton>
    <div v-if="enableGap" style="height:10px"></div>
</template>


<script>
import ArticleUserCardVue from './ArticleUserCard.vue'

import { getIsLikedArticle, getArticleLikedCount, getArticleCommentCount, likeArticle, cancelLikeArticle } from '@/utils/api/articles'
import { getUserProfile } from '@/utils/api/users'
import { parseTime } from "@/utils/timeparse"
//https://github.com/Justineo/vue-clamp/issues/55
//https://www.w3docs.com/snippets/css/how-to-break-line-without-using-br-tag-in-css.html
import VueClamp from './VueClamp.vue'
import { ImagePreview } from 'vant';
import 'vant/es/image-preview/style';


export default {
    name: 'ArticleSummaryCard',
    data() {
        return {
            isLoading: true,
            isLiked: false,
            author: null,
            windowWidth: document.documentElement.clientWidth,
            windowHeight: document.documentElement.clientHeight,
            likedCount: 0,
            commentCount: 0,
            isWidthWise: false,
        }
    },
    components: {
        VueClamp,
        'author-card': ArticleUserCardVue,
    },
    props: ['articleInfo', 'enableGap'],
    emits: ['clickContent', 'clickHead'],
    methods: {
        async loadAuthor() {
            this.author = await getUserProfile(this.articleInfo.user)
        },
        async loadIsLiked() {
            try {
                const result = await getIsLikedArticle(this.articleInfo.id)
                this.isLiked = result.data.liked
            } catch (error) {
                if (error.response.status === 500) {
                    this.$toast.fail("服务器出现了一点问题")
                }
                else {
                    this.$toast.fail(`加载是否点赞失败\n ${JSON.stringify(error.response.data)}`)
                }
            }
        },
        async loadLikeCount() {
            try {
                const result = await getArticleLikedCount(this.articleInfo.id)
                this.likedCount = result.data.count
            } catch (error) {
                if (error.response.status === 500) {
                    this.$toast.fail("服务器出现了一点问题")
                }
                else {
                    this.$toast.fail(`加载点赞数量失败\n ${JSON.stringify(error.response.data)}`)
                }
            }
        },
        async loadCommentCount() {
            try {
                const result = await getArticleCommentCount(this.articleInfo.id)
                this.commentCount = result.data.count
            } catch (error) {
                if (error.response.status === 500) {
                    this.$toast.fail("服务器出现了一点问题")
                }
                else {
                    this.$toast.fail(`加载评论数量失败\n ${JSON.stringify(error.response.data)}`)
                }
            }
        },
        async startLoad() {
            const tasks = [this.loadAuthor()]
            await Promise.all(tasks)
            this.isLoading = false
        },
        onClickContent() {
            this.$emit('clickContent', this.articleInfo.id)
        },
        showImagePreview(index) {
            ImagePreview({
                images: this.imageList,
                startPosition: index,
            });
        },
        async updateLikeStatus() {
            this.loadIsLiked()
            this.loadLikeCount()
        },
        async onClickLike() {
            //更快的响应
            this.isLiked = true
            this.likedCount++
            try {
                await likeArticle(this.articleInfo.id)
            } catch (error) {
                if (error.response.status === 500) {
                    this.$toast.fail("服务器出现了一点问题")
                }
                else {
                    this.$toast.fail(`点赞失败\n ${JSON.stringify(error.response.data)}`)
                }
            }
            this.updateLikeStatus()
        },
        async onClickCancelLike() {
            //更快的响应
            this.isLiked = false
            this.likedCount--
            try {
                await cancelLikeArticle(this.articleInfo.id)
            } catch (error) {
                if (error.response.status === 500) {
                    this.$toast.fail("服务器出现了一点问题")
                }
                else {
                    this.$toast.fail(`取消点赞失败\n ${JSON.stringify(error.response.data)}`)
                }
            }
            this.updateLikeStatus()
        },
        onClickHead(user_id) {
            this.$emit('clickHead', user_id)
        },
        adjustImage() {
            if (this.imageList.length == 1) {
                const image = new Image()
                image.src = this.imageList[0]
                if (image.naturalWidth > image.naturalHeight) {
                    //纵向变横向
                    this.isWidthWise = true
                }
            }
        }
    },
    computed: {
        article_content() {
            return this.articleInfo.post
        },
        publish_time() {
            return parseTime(this.articleInfo.pub_date)
        },
        article_title() {
            return this.articleInfo.title
        },
        imageList() {
            const result = []
            this.articleInfo.images.forEach((image) => { result.push(image.image_url) })
            return result
        },
        oneImageWidth() {
            if (this.isWidthWise) {
                return this.windowWidth * 0.65
            }
            else {
                return this.windowWidth * 0.45
            }
        },
        oneImageHeight() {
            if (this.isWidthWise) {
                return this.windowHeight * 0.28
            }
            else {
                return this.windowHeight * 0.36
            }
        }
    },
    mounted() {
        this.startLoad()
        this.likedCount = this.articleInfo.like_count
        this.commentCount = this.articleInfo.reply_count
        this.isLiked = this.articleInfo.is_liked
    }
}

</script>

<style lang="scss" scoped>
.article-author-card {
    padding-left: 4%;
}

.article-action-container {
    display: flex;
    justify-content: space-around;

    .article-action-common {
        display: flex;

        .article-action-number {
            display: flex;
            justify-content: center;
            flex-direction: column;
            padding-left: 10px;
        }

        .article-action-empty {
            padding-left: 10px;
            white-space: nowrap;
        }

        .article-action-icon {
            padding-top: 5px;
            padding-bottom: 5px;
        }
    }
}

.article-title {
    text-align: start;
    padding-left: 4%;
    padding-right: 4%;
	padding-top: 1%;
	padding-bottom: 1%;
    font-size: larger;
    font-weight: bolder;
}


.article-content {
    white-space: pre-line;
    word-break: break-word;
    margin: 0;
    text-align: start;
    padding-left: 4%;
    padding-right: 4%;
}

.image-common {
    padding-left: 4%;
    padding-right: 4%;
}

.article-image-1 {
    display: flex;
    justify-content: left;
}

.article-action-divider {
    margin: 0;
    padding-top: 10px;
}

//后续图片时属性与image-common一致
</style>