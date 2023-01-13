<template>
    <van-sticky>
        <van-nav-bar left-arrow @click-left="onClickBack" title="ta的信息" />
    </van-sticky>
	<div style="height:10px"></div>
    <div id="profile">
        <!-- 骨架屏用于加载时占位 -->
        <van-skeleton :row="15" :loading="isLoading">
            <van-cell-group inset>
                <van-cell center class="avatar-uploader" title="头像">
                    <!-- 右侧value插槽展示头像 -->
                    <template #value>
						<van-image
						round
						fit="cover"
						:src="userProfile.avatar_url"
						width="60"
						height="60"
						/>
                    </template>
                </van-cell>

                <van-cell center title="UID" :value="userProfile.id" class="id-uploader" />

                <van-cell center title="昵称" :value="userProfile.nickname" class="id-uploader"/>

                <van-cell center title="性别" :value="gender" class="id-uploader" />

                <van-cell center title="年龄" :value="userProfile.age" class="id-uploader" />
            </van-cell-group>
			
            <van-cell-group inset title="个性签名">
                <van-cell>
                    <template #value>
                        <van-field
                            v-model="userProfile.motto"
                            autosize
                            type="textarea"
                            placeholder="ta很高冷,暂时没有个性签名"
                            readonly
                        />
                    </template>
                </van-cell>
            </van-cell-group>
        

        </van-skeleton>
    </div>
</template>


<script>
import {Gender} from '@/utils/api/me'
import {getUserProfile} from '@/utils/api/users'

export default {
    name: 'OthersProfile',
    data() {
        return {
            isLoading: true, //用户信息是否在加载中
            userProfile: null, //用户信息状态
        }
    },
    computed: {
        user_id() {
            return this.$route.params.user_id
        },
        gender(){
            switch (this.userProfile.gender) { //由数字选项转换为中文
                case Gender.NA:
                    return "不适用";
                case Gender.MALE:
                    return "男";
                case Gender.FEMALE:
                    return "女";
                case Gender.NON_BINARY:
                    return "非二元";
                default:
                    return "无效数据";
            }
        }
    },
    methods: {
        async loadUserProfile() {
            this.userProfile = await getUserProfile(this.user_id)
        },
        onClickBack() {
            this.$router.back()
        }
    },
    mounted(){
        //切换到该页面时更新数据
        this.loadUserProfile().then(() => {this.isLoading = false})
    }
}
</script>


<style lang="scss" scoped>
#profile {
    margin: 0;
    overflow-x: auto;
    color: #323233;
    font-size: 16px;
    font-family: Open Sans,-apple-system,BlinkMacSystemFont,Helvetica Neue,Helvetica,Segoe UI,Arial,Roboto,PingFang SC,miui,Hiragino Sans GB,Microsoft Yahei,sans-serif;
    background-color: #f7f8fa;
    -webkit-font-smoothing: antialiased;
    text-align: start;
}

.motto-content {
    font-size: 18px;
    line-height: 30px;
    :deep(.van-cell__value) {
        min-width: 70%;
        text-align: left;
    }
}

.avatar-uploader {
    padding-top: 5px;
    padding-bottom: 0px;
	height: 100px;
    font-size: 20px;
}
.id-uploader {
    padding-top: 5px;
    padding-bottom: 0px;
	height: 50px;
    font-size: 18px;
    :deep(.van-cell__value) {
        min-width: 70%;
    }
}

.cropper-wrapper {
    width: 90%;
    height: 90%;
    margin: 0 auto;
    z-index: 10;
}
</style>