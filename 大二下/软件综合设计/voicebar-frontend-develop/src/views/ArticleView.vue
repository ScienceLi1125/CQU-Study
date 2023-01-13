<template>
    <!-- 顶部导航栏 -->
    <van-nav-bar fixed title="帖子" left-arrow @click-left="onClickBack" />

    <div style="height:46px"></div>

    <!-- 骨架屏占位加载 -->
    <van-skeleton title avatar :row="3" :loading="loadingArticle">
        <!-- 从上至下,依次为:文章标题、文章作者头部、文章音频播放器、文章正文、文章图片显示区域、文章底部操作栏 -->
        <van-cell-group :border="true">
            <!-- 文章标题 -->
            <div class="head-article-title-text">
                {{ article_title }}
            </div>
            <van-divider :style="{ margin: '0', color: '#ffffff', borderColor: '#ffffff' }" />
            <!-- 文章作者头部 -->
            <author-card @clickHead="onClickArticleHead" :user_id="author.id" :enableGap="true" :nickname="author.nickname" :avatar_url="author.avatar_url"
                :publish_time="publish_time" :ip_loc="ip" :is_admin="author.is_admin"/>

            <!-- 文章音频播放器 -->
            <Player v-if="articleInfo.voice_url" theme="light" style="--vm-player-theme: #e86c8b;">
                <Audio>
                    <source :data-src="articleInfo.voice_url" type="audio/mp3" />
                </Audio>
                <DefaultUi noSettings/>
            </Player>

            <div style="height:10px"></div>

            <!-- 文章正文 -->
            <div class="article-content">
                {{ article_content }}
            </div>

            <!-- 文章图片显示区域 -->
            <div v-if="imageList.length"  style="height:20px"></div>  <!-- 需要显示图片时 预留一点空间 -->

            <div v-if="imageList.length === 1" class="article-image-1 image-common">  <!-- 只有一张图片 -->
                <van-image
                fit="cover"
                :src="imageList[0]"
                @click="showImagePreview(0)"
                />
            </div>

            <div v-else-if="imageList.length === 2" class="article-image-2 image-common"> <!-- 只有两张图片 -->
                <van-row gutter="5">
                    <van-col span="12">
                        <van-image
                        fit="cover"
                        :height="0.46 * windowWidth"
                        :src="imageList[0]"
                        @click="showImagePreview(0)"
                        />
                    </van-col>
                    <van-col span="12">
                        <van-image
                        fit="cover"
                        :height="0.46 * windowWidth"
                        :src="imageList[1]"
                        @click="showImagePreview(1)"
                        />
                    </van-col>
                </van-row>
            </div>

            <div v-else-if="imageList.length === 3" class="article-image-3 image-common"> <!-- 只有三张图片 -->
                <van-row gutter="5">
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[0]"
                        @click="showImagePreview(0)"
                        />
                    </van-col>
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[1]"
                        @click="showImagePreview(1)"
                        />
                    </van-col>
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[2]"
                        @click="showImagePreview(2)"
                        />
                    </van-col>
                </van-row>
            </div>

            <div v-else-if="imageList.length === 4" class="article-image-4 image-common"> <!-- 只有四张图片 -->
                <van-row gutter="5">
                    <van-col span="12">
                        <van-image
                        fit="cover"
                        :height="0.47 * windowWidth"
                        :src="imageList[0]"
                        @click="showImagePreview(0)"
                        />
                    </van-col>
                    <van-col span="12">
                        <van-image
                        fit="cover"
                        :height="0.47 * windowWidth"
                        :src="imageList[1]"
                        @click="showImagePreview(1)"
                        />
                    </van-col>
                </van-row>
                <van-row gutter="5">
                    <van-col span="12">
                        <van-image
                        fit="cover"
                        :height="0.47 * windowWidth"
                        :src="imageList[2]"
                        @click="showImagePreview(2)"
                        />
                    </van-col>
                    <van-col span="12">
                        <van-image
                        fit="cover"
                        :height="0.47 * windowWidth"
                        :src="imageList[3]"
                        @click="showImagePreview(3)"
                        />
                    </van-col>
                </van-row>
            </div>

            <div v-else-if="imageList.length === 5 || imageList.length === 6" class="article-image-5_6 image-common"> <!-- 只有5~6张图片 -->
                <van-row gutter="5">
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[0]"
                        @click="showImagePreview(0)"
                        />
                    </van-col>
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[1]"
                        @click="showImagePreview(1)"
                        />
                    </van-col>
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[2]"
                        @click="showImagePreview(2)"
                        />
                    </van-col>
                </van-row>
                <van-row gutter="5">
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[3]"
                        @click="showImagePreview(3)"
                        />
                    </van-col>
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[4]"
                        @click="showImagePreview(4)"
                        />
                    </van-col>
                    <van-col v-if="imageList.length === 6" span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[5]"
                        @click="showImagePreview(5)"
                        />
                    </van-col>
                </van-row>
            </div>

            <div v-else-if="imageList.length >= 7" class="article-image-7_8_9 image-common"> <!-- 只有7~9张图片 -->
                <van-row gutter="5">
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[0]"
                        @click="showImagePreview(0)"
                        />
                    </van-col>
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[1]"
                        @click="showImagePreview(1)"
                        />
                    </van-col>
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[2]"
                        @click="showImagePreview(2)"
                        />
                    </van-col>
                </van-row>
                <van-row gutter="5">
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[3]"
                        @click="showImagePreview(3)"
                        />
                    </van-col>
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[4]"
                        @click="showImagePreview(4)"
                        />
                    </van-col>
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[5]"
                        @click="showImagePreview(5)"
                        />
                    </van-col>
                </van-row>
                <van-row gutter="5">
                    <van-col span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[6]"
                        @click="showImagePreview(6)"
                        />
                    </van-col>
                    <van-col v-if="imageList.length >= 8" span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[7]"
                        @click="showImagePreview(7)"
                        />
                    </van-col>
                    <van-col v-if="imageList.length === 9" span="8">
                        <van-image
                        fit="cover"
                        :height="0.3 * windowWidth"
                        :width="0.3 * windowWidth"
                        :src="imageList[8]"
                        @click="showImagePreview(8)"
                        />
                    </van-col>
                </van-row>
            </div>
            <!-- 文章图片显示区域结束 -->
            <div style="height:10px"></div>

            <!-- 文章底部操作栏 -->
            <div class="article-action-container">
                <van-icon class="article-action-icon" size="25" name="chat-o" @click="onClickWriteComment"/>
                <van-icon v-if="!isLiked" class="article-action-icon" size="25" name="good-job-o" @click="onClickLike"/>
                <van-icon v-else class="article-action-icon" color="#FB7299" size="25" name="good-job" @click="onClickCancelLike"/>
            </div>

            <div style="height:10px"></div>

        </van-cell-group>


    </van-skeleton>

    <div style="height:10px"></div>

    <!-- 骨架屏占位加载 -->
    <van-skeleton title avatar :row="10" :loading="loadingArticle">
        <van-cell-group>
                <van-cell>
                    <!-- 互动区信息头部 -->
                    <template #title>
                        <div class="article-interaction-comment-container">
                            评论数 {{ article_comment_count }}
                        </div>
                    </template>
                    <template #value>
                        <div class="article-interaction-zan-container">
                            点赞 {{ article_liked_count }}
                        </div>
                    </template>
                </van-cell>
                
            <!-- 用list存放评论卡片 -->
            <van-list v-model:loading="commentLoading" :finished="commentFinished" :finished-text="commentListFinishedText"
                @load="onLoadComments">
                <comment-card v-for="item in commentInfoList" :key="item.id" :commentInfo="item" @clickHead="onClickCommentHead"/>
            </van-list>

        </van-cell-group>

        <div style="height:50px"></div>

        <!-- 底部发表评论区域Popup -->
        <van-popup v-model:show="showCommentPopup" position="bottom" >
            <div class="write-comment-container">
                <div style="display:flex;">
                    <van-image
                    round
                    fit="cover"
                    :src="userProfile.avatar_url"
                    width="45"
                    height="45"
                    />
                </div>
                <div style="width:100%;padding-left: 10px;">
                    <van-cell-group inset class="write-comment-group">
                        <van-field
                            ref="commentTextarea"
                            class="write-comment-textarea"
                            enterkeyhint="send"
                            autosize
                            autofocus
                            type="textarea"
                            @keydown.enter.prevent="sendComment"
                            v-model="comment_text"
                            placeholder="写评论..."
                        />
                    </van-cell-group>
                </div>
            </div>
        </van-popup>

        <!-- 底部发表评论区域,点击触发Popup -->
        <van-action-bar style="padding-left:3%;padding-right: 3%;">
            <van-action-bar-icon @click="onClickWriteComment">
                <template #icon>
                    <div style="display:flex;">
                        <van-image
                        round
                        fit="cover"
                        :src="userProfile.avatar_url"
                        width="45"
                        height="45"
                        />
                    </div>
                </template>
            </van-action-bar-icon>

            <van-field
                v-model="comment_text"
                readonly
                :autosize="{ maxHeight: 24}"
                :rows="1"
                type="textarea"
                placeholder="写评论..."
                @click-input.stop="onClickWriteComment"
            />

        </van-action-bar>

    </van-skeleton>

</template>


<script>


import ArticleUserCardVue from '@/components/ArticleUserCard.vue';
import { Player, Audio, DefaultUi } from '@vime/vue-next';
//support: DefaultUi not adjusted well when deployed
//https://github.com/vime-js/vime/issues/165

//默认加载从jsdelivr  需要在node_modules中修改文件！ @vime/vue-next/dist/custom-elements/index.js

import { ImagePreview } from 'vant';

import { getArticleDetail, getArticleLikedCount, getAllComments, publishComment, likeArticle, cancelLikeArticle, getIsLikedArticle} from '@/utils/api/articles'
import { getUserProfile } from '@/utils/api/users'
import {getSelfProfile} from '@/utils/api/me'
import { parseTime } from '@/utils/timeparse'
import ArticleCommentCardVue from '@/components/ArticleCommentCard.vue';
import {storeUserProfile,retrieveUserProfile} from '@/utils/storage'



export default {
    name: 'ArticleView',
    components: {
        'author-card': ArticleUserCardVue,
        Player,
        Audio,
        DefaultUi,
        'comment-card': ArticleCommentCardVue,
    },
    data() {
        return {
            loadingArticle: true, //文章信息是否仍在加载
            articleInfo: null, //文章信息状态保存
            author: null, //文章作者信息状态保存
            isLiked: false, //是否已喜欢文章
            article_liked_count: null, //文章点赞数
            article_comment_count: null, //文章评论数
            commentLoading: false, //文章评论区List是否在加载
            commentFinished: false, //文章评论区是否无更多信息可加载
            commentInfoList: [], //文章评论区List信息绑定
            loadingPage: 1, //文章评论当前已加载到的页数
            userProfile: null, //当前登录用户个人信息状态,底部评论区需显示用户头像用
            comment_text: "", //评论区输入绑定
            showCommentPopup: false, //是否弹出底部评论区Popup
            windowWidth: document.documentElement.clientWidth,
            windowHeight: document.documentElement.clientHeight,
        }
    },
    computed: {
		ip() {
			return this.articleInfo.ip_loc
		},
        article_id() {
            return this.$route.params.article_id
        },
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
            this.articleInfo.images.forEach((image) => {result.push(image.image_url)})
            return result
        },
        commentListFinishedText() {
            if (this.article_comment_count) {
                return "没有更多了"
            }
            return "成为第一个写评论的人吧"
        },
    },
    methods: {
        onClickBack() {
            this.$router.back()
        },
        async startLoad() { //加载文章必须的信息
            const article_task = getArticleDetail(this.article_id)
            this.articleInfo = await article_task
            const author_task = getUserProfile(this.articleInfo.user)
            this.article_comment_count = this.articleInfo.reply_count
            this.article_liked_count = this.articleInfo.like_count
            this.isLiked = this.articleInfo.is_liked
            this.author = await author_task
            const localProfile = retrieveUserProfile()
            this.userProfile = localProfile
            this.loadingArticle = false
            const profileResult = await getSelfProfile()
            this.userProfile = profileResult.data
            storeUserProfile(profileResult.data)
        },
        async onLoadComments() { //评论区List需要加载更多时调用的函数
            const data = await getAllComments(this.article_id, this.loadingPage)
            this.commentInfoList.push(...data)
            this.commentLoading = false
            this.loadingPage = this.loadingPage + 1
            if (!data.length) {
                this.commentFinished = true
            }
        },
        onClickWriteComment() {
            this.showCommentPopup = true
        },
        async sendComment() { //按下回车,发送评论
            this.showCommentPopup = false
            this.$toast.loading("上传评论中")
            try {
                await publishComment(this.article_id,this.comment_text)
                this.$toast.clear()
                this.$toast.success("评论成功")
            } catch(error) {
                this.$toast.clear()
                if (error.response.status === 500) {
                    this.$toast.fail("服务器出现了一点问题")
                }
                else {
                    this.$toast.fail(`发布评论失败\n ${JSON.stringify(error.response.data)}`) 
                }
            }
            //发布评论后重新加载文章数据
            this.comment_text = ""
            this.startLoad()
            this.commentInfoList = []
            this.loadingPage = 1
            this.commentFinished = false
        },
        async updateLikeStatus() { //对文章赞/取消赞后 赞数的更新 赞的状态的更新
            const update_count_result = await getArticleLikedCount(this.article_id)
            const update_liked_result = await getIsLikedArticle(this.article_id)
            this.article_liked_count = update_count_result.data.count
            this.isLiked = update_liked_result.data.liked
        },
        async onClickLike() { //点赞操作触发函数
            //更快的响应
            this.isLiked = true
            this.article_liked_count++
            try {
                await likeArticle(this.article_id)
            } catch(error) {
                if (error.response.status === 500) {
                    this.$toast.fail("服务器出现了一点问题")
                }
                else {
                    this.$toast.fail(`点赞失败\n ${JSON.stringify(error.response.data)}`)
                }
            }
            this.updateLikeStatus()
        },
        async onClickCancelLike() { //取消点赞操作触发函数
            //更快的响应
            this.isLiked = false
            this.article_liked_count--
            try {
                await cancelLikeArticle(this.article_id)
            } catch(error) {
                if (error.response.status === 500) {
                    this.$toast.fail("服务器出现了一点问题")
                }
                else {
                    this.$toast.fail(`取消点赞失败\n ${JSON.stringify(error.response.data)}`)
                }
            }
            this.updateLikeStatus()
        },
        showImagePreview(index) { //文章图片点击放大查看
            ImagePreview({
                images: this.imageList,
                startPosition: index,
            });
        },
        onClickArticleHead(user_id) { //点击文章作者头部
            this.$router.push({path:`/user/${user_id}`})
        },
        onClickCommentHead(user_id) { //点击评论作者头部
            this.$router.push({path:`/user/${user_id}`})
        }
    },
    mounted() {
        this.startLoad()
    }
}

</script>





<style lang="scss" scoped>
.head-article-title-text {
    padding-left: 20px;
	padding-right: 20px;
    padding-bottom: 5px;
	padding-top: 8px;
    text-align: left;
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

.article-interaction-comment-container {
    text-align: left;
}

.article-interaction-zan-container {
    color: #323233;
}

.write-comment-container {
    display:flex;
    padding-left: 3%;
    padding-right: 3%;
    padding-top: 10px;
    padding-bottom: 10px;
    .write-comment-group {
        margin: 0;
        .write-comment-textarea {
            background-color: #f5f6f7;
        }
    }
}

.article-action-container {
    display: flex;
    justify-content: space-around;
    .article-action-icon {
        padding-top: 5px;
        padding-bottom: 5px;
    }
}

.image-common {
    padding-left: 4%;
    padding-right: 4%;
}

.article-image-1 {
    display: flex;
    justify-content: left;
}


</style>