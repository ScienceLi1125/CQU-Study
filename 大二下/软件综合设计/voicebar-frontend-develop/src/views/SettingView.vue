<template>
	<!-- 使用Config Provider自定义Vant组件主题 -->
	<van-config-provider :theme-vars="themeVars">
		<van-nav-bar fixed title="设置" left-arrow @click-left="onClickLeft"/>
		<!-- fixed后需将后续元素往下顶 否则导航栏会遮挡内容 -->
		<div style="height:46px"></div>
		<div class="cell-content"></div>
		<!-- 跳转至authing用户中心进行账户安全相关操作 -->
		<van-cell value="密码修改" is-link url="https://aiekefnkoldmbnng-demo.authing.cn/u" icon="edit"/>
		<!-- 分割线 -->
		<div style="background-color:rgb(240, 240, 240); height:1px;"></div>
		<van-cell value="AI设置" is-link icon="desktop-o" clickable @click="aiClick" />
		<!-- 分割线 -->
		<div style="background-color:rgb(240, 240, 240); height:1px;"></div>
		<van-cell value="关于我们" is-link icon="friends-o" clickable @click="aboutClick"/>

		<!-- 将退出登录与上面的设置项分开 -->
		<div style="height: 30px;"></div>
		<van-config-provider :theme-vars="LogoutTheme">
			<van-cell title="退出登陆" clickable @click="logOut" />
		</van-config-provider>
	</van-config-provider>
</template>

<script>
import {getAuthClientWithToken,retrieveAuthingUser} from '@/utils/authing'
import {removeUserProfile} from '@/utils/storage'

const themeVars = {
	cellLineHeight: '30px',
	cellFontSize: '18px',
	cellIconSize:'18px',
}

const LogoutTheme = {
	cellTextColor: 'red',
}

export default{
	name:'SettingView',
	data () {
		return {
			user: null,
		}
	},
	computed: {
		themeVars () {
			return themeVars
		},
		LogoutTheme () {
			return LogoutTheme
		}
	},
	methods: {
		onClickLeft() {history.back()},
		async logOut() { //清除localStorage存储的信息
			await getAuthClientWithToken(this.user.token).logout() //向Authing通告登出
			removeUserProfile()
			this.$toast.success("已登出")
			localStorage.clear()
			this.$router.replace({path:'/login'})
		},
		aiClick() {
			this.$toast.success("敬请期待")
		},
		aboutClick() {
			this.$toast.success("o的迷妹们开发的App")
		},
	},
	mounted() {
		retrieveAuthingUser().then( //从localStorage中取得Authing用户信息
		(user)=>{this.user = user;})
	},
};

</script>

<style lang="scss" scoped>
	.cell-content {
		padding-top: 10px;
	}
</style>