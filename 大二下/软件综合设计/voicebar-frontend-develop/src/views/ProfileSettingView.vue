<template>
    <van-sticky>
        <!-- 导航栏 -->
        <van-nav-bar left-arrow @click-left="onClickNavLeft" title="个人信息" />
    </van-sticky>
	<div style="height:10px"></div>
    <!-- 个人信息设置容器 -->
    <div id="profile">
        <!-- 使用Skeleton 骨架屏占位，当所需信息加载完毕后正常显示 -->
        <van-skeleton :row="15" :loading="isLoading">
            <!-- 个人信息cell-group,启用圆角,不包含个性签名 -->
            <van-cell-group inset>
                <!-- 头像展示栏 -->
                <van-cell center clickable @click.stop="onClickAvatar" class="avatar-uploader" title="头像">
                    <!-- cell的value插槽,即cell的右半部分插槽,用于展示头像 -->
                    <template #value>
                        <!-- 使用ref,可主动调用选择文件,用于监听整个cell点击事件时正确弹出选择文件框 -->
                        <van-uploader @click.stop :after-read="afterSelectAvatar" ref="avatarUploader">
                            <van-image
                            round
                            fit="cover"
                            :src="userProfile.avatar_url"
                            width="60"
                            height="60"
                            />
                        </van-uploader>
                    </template>
                </van-cell>

                <!-- 展示用户ID -->
                <van-cell center clickable title="UID" :value="userProfile.id" class="id-uploader"/>

                <!-- 展示与修改用户名 -->
                <van-cell center clickable title="昵称" :value="userProfile.nickname" class="id-uploader" @click="nameClick" is-link/>
                <v-dialog v-model:show="showChangeName" title="更改昵称" close-on-click-overlay show-cancel-button @confirm="changeName" :before-close="validateName">
                    <van-field
                    v-model="changeNameBind"
                    label="新用户名"
                    maxlength="10"
                    show-word-limit
                    >
                    </van-field>
                </v-dialog>

                <!-- 展示与修改性别 -->
                <van-cell center clickable title="性别" :value="gender" class="id-uploader" @click="genderClick" is-link/>
                <van-popup :show="showGenderPopup" close-on-click-overlay @close="closeOverlay" round position="bottom" :style="{ height: '30%' }">
                    <van-picker
                    title="更改性别"
                    :columns="genders"
                    @confirm="onGenderConfirm"
                    @cancel="onGenderCancel"
                    :default-index="userProfile.gender-1"
                    />
                </van-popup>

                <!-- 展示与修改年龄 -->
                <van-cell center clickable title="年龄" :value="userProfile.age" class="id-uploader" @click="ageClick" is-link    />
                <van-popup :show="showAgePopup" close-on-click-overlay @close="closeOverlay" round position="bottom" :style="{ height: '30%' }">
                    <van-picker
                    title="更改年龄"
                    :columns="ages"
                    @confirm="onAgeConfirm"
                    @cancel="onAgeCancel"
                    :default-index="userProfile.age-1"
                    />
                </van-popup>

            </van-cell-group>

            <!-- 用于展示和修改个性签名的cell-group 可利用其title属性保持页面美观-->
            <van-cell-group inset title="个性签名">
                <van-cell clickable @click="mottoClick">
                    <template #value>
                        <van-field
                            v-model="userProfile.motto"
                            autosize
                            type="textarea"
                            placeholder="介绍一下自己吧"
                            readonly
                        />
                    </template>
                </van-cell>
                <van-popup :show="showMottoPopup" close-on-click-overlay position="bottom" :style="{ height: '40%' }" @close="changeMotto">
                    <van-field
                        v-model="changeMottoBind"
                        autosize
                        type="textarea"
                        maxlength="50"
                        placeholder="请输入个性签名"
                        show-word-limit
                    />
                </van-popup>
            </van-cell-group>
        
            <!-- 图像裁剪遮罩层 -->
            <van-overlay :show="showCropperOverlay" :lock-scroll="false">
                <van-nav-bar
                    title="头像裁剪"
                    left-arrow
                    @click-left="onClickCropperLeft"
                    @click-right="onClickCropperConfirm"
                >
                    <template #right>
                        <van-icon name="success" size="18" />
                    </template>
                </van-nav-bar>
                <div class="cropper-wrapper">
                    <vue-cropper
                    :img="cropperImage"
                    :canMove="false"
                    outputType="png"
                    autoCrop
                    :autoCropWidth="150"
                    :autoCropHeight="150"
                    fixed
                    centerBox
                    ref="cropper"
                    class="avatar-cropper"
                    />
                </div>
            </van-overlay>

        </van-skeleton>
    </div>
</template>


<script>
import {Gender} from '@/utils/api/me'
import {storeUserProfile,retrieveUserProfile} from '@/utils/storage'
import {getSelfProfile,updateSelfProfile,updateAvatar} from '@/utils/api/me'
import { Dialog } from 'vant'
import 'vant/es/dialog/style';

//用于修改年龄,生成1~149的选项,控制用户只能在1~149之间选择
const ages = []
for (let age = 1; age <= 149; age++) {
    ages.push(age)
}

//用于修改性别的选项
const genders = ["不适用","男","女","非二元"]

export default {
    name: 'ProfileSettingView',
    components: {
        'v-dialog': Dialog.Component, //vant3 bug 要以组件形式使用dialog必须这样手动声明,全局引入无效
    },
    data() {
        return {
            isLoading: true, //标识必要信息是否加载完毕
            showAgePopup: false, //控制是否展示选择年龄Popup
            showGenderPopup: false, //控制是否展示选择性别Popup
            showChangeName: false, //控制是否展示更改用户名Dialog
            changeNameBind: "", //用于双向绑定更改用户名Dialog中输入框的内容
            showMottoPopup: false, //控制是否展示更改个性签名Popup
            changeMottoBind: "", //用于双向绑定更改个性签名Popup中输入框的内容
            showCropperOverlay: false, //控制是否展示头像裁剪叠加层
            cropperImage: null, //绑定VueCropper裁剪的图像来源
            userProfile: null, //用于存储用户个人信息状态
        }
    },
    computed: {
        gender(){ //将后端给的数字性别选项转换为中文表示
            switch (this.userProfile.gender) {
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
        },
        ages(){ //暴露之前定义的年龄选项
            return ages
        },
        genders(){ //暴露之前定义的性别选项
            return genders
        }
    },
    methods: {
        //在此页,用户一定已经登陆了
        loadLocalProfile(){
            //从本地缓存localStorage中读取用户个人信息
            this.userProfile = retrieveUserProfile()
        },
        async loadNetworkProfile(){
            //从后端拉取个人信息
            const profileResult = await getSelfProfile()
            //更新localStorage中的profile值
            storeUserProfile(profileResult.data)
            this.userProfile = profileResult.data
        },
        ageClick(){
            this.showAgePopup = true
        },
        onAgeCancel(){
            this.showAgePopup = false
        },
        async updateProfile(profile){ //更新本地及服务器上的用户个人信息
            //优先更改本地,快速响应
            this.userProfile =profile
            storeUserProfile(profile)
            await updateSelfProfile(profile)
            this.$toast.success("已保存更改")
        },
        async onAgeConfirm(value){
            this.showAgePopup = false
            //更新localStorage,并更新至服务器
            const profile = this.userProfile
            profile.age = value
            this.updateProfile(profile)
        },
        genderClick() {
            this.showGenderPopup = true
        },
        onGenderCancel(){
            this.showGenderPopup = false
        },
        async onGenderConfirm(value,index){
            this.showGenderPopup = false
            //更新localStorage,并更新至服务器
            const profile = this.userProfile
            profile.gender = index+1
            this.updateProfile(profile)
        },
        nameClick(){
            //将输入框中的内容提前绑定好
            this.changeNameBind = this.userProfile.nickname
            this.showChangeName = true
        },
        async changeName(){
            const profile = this.userProfile
            profile.nickname = this.changeNameBind
            //更新localStorage,并更新至服务器
            this.updateProfile(profile)
        },
        async validateName(action){ //控制用户不能输入空白名
            if (action === "cancel"){
                return true
            }
            //校验 1.不能是空名 2.不能全是空白
            if (this.changeNameBind.trim() === "") {
                this.$toast.fail("昵称不能为空")
                return false
            }
            return true
        },
        mottoClick(){
            this.changeMottoBind = this.userProfile.motto
            this.showMottoPopup = true
        },
        async changeMotto(){
            this.showMottoPopup = false
            const profile = this.userProfile
            profile.motto = this.changeMottoBind
            //更新localStorage,并更新至服务器
            this.updateProfile(profile)
        },
        closeOverlay(){ //年龄性别的关闭共用
            this.showAgePopup = false
            this.showGenderPopup = false
        },
        onClickNavLeft(){
            this.$router.back()
        },
        onClickAvatar() { //手动调起选择文件框
            this.$refs.avatarUploader.chooseFile()
        },
        afterSelectAvatar(file) { //Uploader读入文件后,将文件传给图像裁剪模块,并显示
            //https://github.com/xyxiao001/vue-cropper/issues/412
            //不可直接传入blob
            this.cropperImage = window.URL.createObjectURL(file.file)
            this.showCropperOverlay = true
        },
        onClickCropperLeft() {
            this.showCropperOverlay = false
        },
        async onClickCropperConfirm() { //图像裁剪确认后上传
            this.$refs.cropper.getCropBlob(file => {this.uploadAvatar(file)})
            this.showCropperOverlay = false
        },
        async uploadAvatar(file) {
            this.$toast.loading({
                message: '头像上传中',
                forbidClick: true,
            })
            await updateAvatar(file)
            await this.loadNetworkProfile()
            this.$toast.clear()
            this.$toast.success("上传成功")
        }
    },
    mounted(){
        //切换到该页面时更新数据
        this.loadLocalProfile()
        this.loadNetworkProfile().then(()=>{this.isLoading=false})
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

.avatar-cropper {
    :deep(.cropper-crop-box) {
        .cropper-view-box {
            -webkit-border-radius: 999px;
            -moz-border-radius: 999px;
            border-radius: 999px;
            //IOS兼容
            transform: rotate(0deg);
            -webkit-transform: rotate(0deg);
            overflow: hidden;
        }
    }
}

</style>