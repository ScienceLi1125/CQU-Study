<template>
	<div style="height: 30px;background-color: white;"></div>
	<!-- 骨架屏占位加载 -->
	<van-skeleton :loading="isLoading" :row="6">
		<van-cell center to="/me/profile">
			<!-- title即cell左侧插槽展示用户信息 -->
			<template #title>
				<div class="head-title-container" style="width: 90%;">
					<div class="head-avatar-container">
						<van-image round fit="cover" width="100px" height="100px" :src="userProfile.avatar_url" />
					</div>
					<div class="head-info-container">
						<p style="font-size:1.2em;line-height:10px;margin-left:15px;font-weight:700;white-space: nowrap;">
							<span :style="{color: nickname_color}">{{ userProfile.nickname }}</span> <van-tag v-if="is_self_admin" type="success">管理员</van-tag>
						</p>
						<p style="line-height:5px;margin-left: 15px;margin-top: 5px;"><span
								style="color:gray;">关注</span><span>&#8195;</span><span
								style="font-size: 20px;font-weight: 700">{{ userProfile.following_count }}</span></p>
						<p style="line-height:5px;margin-left: 15px;"><span
								style="color: gray;">粉丝</span><span>&#8195;</span><span
								style="font-size: 20px;font-weight: 700">{{ userProfile.follower_count }}</span></p>
					</div>
				</div>
			</template>
			<template #right-icon>
				<van-icon name="arrow" color="rgb(150,150,150)" />
			</template>
		</van-cell>
	</van-skeleton>
	<div style="height:10px"></div>
	
	<!-- 各种选项摆放 -->
	<van-config-provider center :theme-vars="themeVars">
		<div style="display: flex;">
			<div class="label-icon">
				<van-icon name="contact" color="rgb(9, 215, 2)" size="25" style="padding-left:30%" />
			</div>
			<div class="label-font">
				<van-cell title="我的关注" style="padding-left:0%" is-link to="/me/following" />
			</div>
		</div>
		<div style="display: flex;">
			<div class="label-icon">
				<van-icon name="friends-o" color="rgb(255, 75, 177)" size="25" style="padding-left:30%" />
			</div>
			<div class="label-font">
				<van-cell title="我的粉丝" style="padding-left:0%" is-link to="/me/follower" />
			</div>
		</div>
		<div style="height:10px"></div>

		<div style="display: flex;">
			<div class="label-icon">
				<van-icon name="comment-o" color="rgba(169,48,239,255)" size="25" style="padding-left:30%" />
			</div>
			<div class="label-font">
				<van-cell title="我的文章" style="padding-left:0%" is-link to="/me/article" />
			</div>
		</div>
		<div style="display: flex;">
			<div class="label-icon">
				<van-icon name="comment-circle-o" color="orange" size="25" style="padding-left:30%" />
			</div>
			<div class="label-font">
				<van-cell title="我的评论" style="padding-left:0%" is-link to="/me/comment" />
			</div>
		</div>
		<div style="height:10px"></div>

		<div style="display: flex;">
			<div class="label-icon">
				<van-icon name="setting-o" color="#1989FA" size="25" style="padding-left:30%" />
			</div>
			<div class="label-font">
				<van-cell title="设置" style="padding-left:0%" is-link to="/me/setting" />
			</div>
		</div>
		<div style="height:10px"></div>
	</van-config-provider>
</template>
<script>
import { getSelfProfile } from '@/utils/api/me'
import { storeUserProfile, retrieveUserProfile } from '@/utils/storage'

const themeVars = {
	cellLineHeight: '30px',
	cellFontSize: '18px',
}

export default {
	name: 'MyView',
	data() {
		return {
			isLoading: true, //指示信息加载状态
			userProfile: null, //绑定用户信息状态
		}
	},
	computed: {
		themeVars() {
			return themeVars
		},
		is_self_admin() {
			return this.userProfile?.is_admin
		},
		nickname_color() {
			if(this.userProfile.is_admin) {
				return '#0DC160'
			}
			else {
				return '#FFBF65'
			}
		},
		dynamic_nickname() {
			const font_len = this.userProfile.nickname.length
			const nickname = this.userProfile.nickname
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
	},
	methods: {
		loadLocalProfile() {
			const profile = retrieveUserProfile()
			this.userProfile = profile
		},
		async loadNetworkProfile() {
			try {
				const profileResult = await getSelfProfile()
				//更新localStorage中的profile值
				storeUserProfile(profileResult.data)
				this.userProfile = profileResult.data
			} catch (error) {
				if (error.response.status === 500) {
					this.$toast.fail("服务器出现了一点问题")
				}
				else {
					this.$toast.fail(`获取个人资料失败\n${JSON.stringify(error.response.data)}`)
				}
			}
		},
	},
	mounted() {
		this.loadLocalProfile()
		this.loadNetworkProfile().then(() => { this.isLoading = false })
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