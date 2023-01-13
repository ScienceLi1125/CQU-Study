<template>

	<van-sticky>
		<!-- 顶部导航栏复用 -->
		<van-nav-bar v-if="isSelf" fixed left-arrow @click-left="onClickNavLeft" title="我的信息" />
		<van-nav-bar v-else fixed left-arrow @click-left="onClickNavLeft" title="ta的信息" />
	</van-sticky>

	<!-- 骨架屏占位加载 -->
	<van-skeleton :row="15" :loading="isLoading">

		<div style="height:46px"></div>

		<!-- 点击头像前往的位置由复用状态决定 -->
		<van-cell center :to="avatarTo">
			<template #title>
				<!-- 左侧title插槽显示圆形头像与用户信息 -->
				<div class="head-title-container" style="width: 100%;">
					<div class="head-avatar-container">
						<van-image round fit="cover" width="100px" height="100px"
							:src="userInfo.avatar_url" />
					</div>
					<div class="head-info-container">
						<p style="font-size:1.2em;line-height:10px;margin-left:15px;font-weight:700;white-space: nowrap;">
							<span :style="{color: nickname_color}">{{userInfo.nickname}}</span> <van-tag v-if="is_user_admin" type="success">管理员</van-tag>
						</p>
						<p style="line-height:5px;margin-left: 15px;margin-top: 5px;"><span
								style="color:gray;">关注</span><span>&#8195;</span><span
								style="font-size: 20px;font-weight: 700">{{userInfo.following_count}}</span></p>
						<p style="line-height:5px;margin-left: 15px;"><span
								style="color: gray;">粉丝</span><span>&#8195;</span><span
								style="font-size: 20px;font-weight: 700">{{userInfo.follower_count}}</span></p>
					</div>
				</div>
			</template>
			<template #right-icon>
				<van-icon name="arrow" color="rgb(150,150,150)" />
			</template>
		</van-cell>

		<!-- 选项,根据复用状态变化 -->
		<div style="height:10px"></div>
		<van-config-provider center :theme-vars="themeVars">

			<div v-if="isSelf" style="display: flex;">
				<div class="label-icon">
					<van-icon name="contact" color="rgb(9, 215, 2)" size="25" style="padding-left:30%" />
				</div>
				<div class="label-font">
					<van-cell title="我的关注" style="padding-left:0%" is-link :to="`/me/following`" />
				</div>
			</div>

			<div v-else style="display: flex;">
				<div class="label-icon">
					<van-icon name="contact" color="rgb(9, 215, 2)" size="25" style="padding-left:30%" />
				</div>
				<div class="label-font">
					<van-cell title="ta的关注" style="padding-left:0%" is-link :to="`/user/${userInfo.id}/following`" />
				</div>
			</div>

			<div v-if="isSelf" style="display: flex;">
				<div class="label-icon">
					<van-icon name="friends-o" color="rgb(255, 75, 177)" size="25" style="padding-left:30%" />
				</div>
				<div class="label-font">
					<van-cell title="我的粉丝" style="padding-left:0%" is-link :to="`/me/follower`" />
				</div>
			</div>

			<div v-else style="display: flex;">
				<div class="label-icon">
					<van-icon name="friends-o" color="rgb(255, 75, 177)" size="25" style="padding-left:30%" />
				</div>
				<div class="label-font">
					<van-cell title="ta的粉丝" style="padding-left:0%" is-link :to="`/user/${userInfo.id}/follower`" />
				</div>
			</div>
			<div style="height:10px"></div>

			<div v-if="isSelf" style="display: flex;">
				<div class="label-icon">
					<van-icon name="comment-o" color="rgba(169,48,239,255)" size="25" style="padding-left:30%" />
				</div>
				<div class="label-font">
					<van-cell title="我的文章" style="padding-left:0%" is-link to="/me/article" />
				</div>
			</div>

			<div v-else style="display: flex;">
				<div class="label-icon">
					<van-icon name="comment-o" color="rgba(169,48,239,255)" size="25" style="padding-left:30%" />
				</div>
				<div class="label-font">
					<van-cell title="ta的文章" style="padding-left:0%" is-link :to="`/user/${userInfo.id}/article`" />
				</div>
			</div>

			<div v-if="isSelf" style="display: flex;">
				<div class="label-icon">
					<van-icon name="comment-circle-o" color="orange" size="25" style="padding-left:30%" />
				</div>
				<div class="label-font">
					<van-cell title="我的评论" style="padding-left:0%" is-link to="/me/comment" />
				</div>
			</div>

			<div v-else style="display: flex;">
				<div class="label-icon">
					<van-icon name="comment-circle-o" color="orange" size="25" style="padding-left:30%" />
				</div>
				<div class="label-font">
					<van-cell title="ta的评论" style="padding-left:0%" is-link :to="`/user/${userInfo.id}/comment`" />
				</div>
			</div>
			<div style="height:10px"></div>
		</van-config-provider>

		<div style="height:70px"></div>
		<div style="display: flex;">
			<div style="width: 33%;"></div>
			<div v-if="!isSelf" style="width: 34%">
				<!-- 查看其他用户信息时会显示的特殊选项 -->
				<van-button v-if="isFollowing" color="#1989FA" round size="large" @click="onClickCancelFollow">
					✓ 已关注
				</van-button>

				<van-button v-else color="#1989FA" round size="large" @click="onClickFollow">
					+ 关注
				</van-button>

				<!-- 登录用户为管理员时会显示的特殊选项 -->
				<div v-if="is_self_admin && !is_user_admin">
					<div style="height:20px"></div>

					<van-button v-if="!is_banned" round size="large" type="warning" @click="onClickBanUser">
						- 封禁用户
					</van-button>

					<van-button v-else round size="large" type="warning" @click="onClickUnBanUser">
						+ 解封用户
					</van-button>
				</div>

				<div v-if="is_self_admin && !is_user_admin">
					<div style="height:20px"></div>

					<van-button round size="large" type="danger" @click="onClickDeleteUser">
						- 删除用户
					</van-button>
				</div>

			</div>
			<div style="width: 33%;"></div>
		</div>
	</van-skeleton>

</template>
<script>
import { getUserProfile } from '@/utils/api/users'
import { deleteUser, banUser, unbanUser } from '@/utils/api/admin'
import { getSelfProfile, getIsFollowingUser, followUser, cancelFollowUser } from '@/utils/api/me'
import { retrieveUserProfile, storeUserProfile } from '@/utils/storage';

const themeVars = {
	cellLineHeight: '30px',
	cellFontSize: '18px',
}



export default {
	name: 'UserInfoView',
	data() {
		return {
			isFollowing: false, //当前登录用户是否关注用户
			userInfo: null, //用户信息状态
			isLoading: true, //必要信息是否仍在加载
			selfUID: 0, //自己的UID
            selfProfile: null, //当前用户的个人信息
		}
	},
	computed: {
		themeVars() { //暴露常量
			return themeVars
		},
		user_id() {
			return this.$route.params.user_id
		},
		isSelf() {
			return this.user_id == this.selfUID
		},
		is_self_admin() {
			return this.selfProfile?.is_admin
		},
		is_user_admin() {
			return this.userInfo?.is_admin
		},
		is_banned() {
			return this.userInfo?.is_banned
		},
		avatarTo() {
			if (this.isSelf) {
				return "/me/profile"
			}
			else {
				return `/user/${this.userInfo.id}/profile`
			}
		},
		nickname_color() {
			if(this.userInfo.is_admin) {
				return '#0DC160'
			}
			else {
				return '#FFBF65'
			}
		},
		dynamic_nickname() {
			const font_len = this.userInfo.nickname.length
			const nickname = this.userInfo.nickname
			var i=0
			var cnt=0
			var ans=''
			for(i=0;i<font_len;i++){
				var tmp=nickname.slice(i,i+1)
				if(tmp>='a' && tmp<='z')	cnt++
				else	cnt+=2
				ans+=tmp
				if(cnt>=10 && i<font_len-1)	return ans+'..'
				else if(cnt>=10 && i==font_len-1)	return ans
			}
			return nickname
		},
		// dynamic_font_size() {
		// 	const font_len = this.userInfo.nickname.length
		// 	if (font_len <= 5) return '25px'
		// 	else {
		// 		const res_len = 125 / font_len
		// 		console.log(res_len)
		// 		return res_len + 'px'
		// 	}
		// },
	},
	methods: {
		onClickNavLeft() {
			this.$router.back()
		},
		async loadUserInfo() { //加载观察用户的信息
			this.userInfo = await getUserProfile(this.user_id)
		},
		async loadIsFollowing() { //加载是否已关注观察用户
			this.isFollowing = await getIsFollowingUser(this.user_id)
		},
		async loadSelfProfile() { //加载自己的信息
			const result = await getSelfProfile()
			this.selfProfile = result.data
			storeUserProfile(result.data)
		},
		async startLoad() {
			const tasks = [this.loadUserInfo(),this.loadIsFollowing(),this.loadSelfProfile()]
			await Promise.all(tasks)
			this.isLoading = false
		},
		async onClickFollow() { //点击关注按钮
			//响应速度优先
			this.isFollowing = true
			this.userInfo.follower_count += 1
			await followUser(this.userInfo.id)
			this.loadUserInfo();this.loadIsFollowing()
		},
		async onClickCancelFollow() { //取消关注按钮
			//响应速度优先
			this.isFollowing = false
			this.userInfo.follower_count -= 1
			await cancelFollowUser(this.userInfo.id)
			this.loadUserInfo();this.loadIsFollowing()
		},
		async onClickDeleteUser() { //管理员删除用户
			await deleteUser(this.user_id)
			this.$router.replace({path:"/"})
		},
		async onClickBanUser() { //管理员封禁用户
			await banUser(this.user_id)
			this.userInfo.is_banned = true
			this.loadUserInfo()
		},
		async onClickUnBanUser() { //管理员解封用户
			await unbanUser(this.user_id)
			this.userInfo.is_banned = false
			this.loadUserInfo()
		}
	},
	mounted() {
        this.selfProfile = retrieveUserProfile()
        this.loadSelfProfile()
		this.startLoad()
		this.selfUID = this.selfProfile.id
	}
};
</script>

<style lang="scss" scoped>
.head-title-container {
	display: flex;
	height: 140px;

	.head-avatar-container {
		display: flex;
		justify-content: center;
		flex-direction: column;
	}

	.head-info-container {
		display: flex;
		align-items: flex-start;
		flex-direction: column;
	}
}

;

.label-icon {
	display: flex;
	width: 15%;
	background-color: white;
	justify-content: center;
	flex-direction: column;
}

;

.label-font {
	display: flex;
	width: 85%;
	text-align: left;
}
</style>