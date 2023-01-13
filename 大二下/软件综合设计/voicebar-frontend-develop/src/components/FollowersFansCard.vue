<template>
	<div>
		<van-cell center :to="`/user/${userInfo.id}`">
			<template #title>
				<div style="width: 90%;display: flex;">
					<div style="display: flex;justify-content: center;flex-direction: column;">
						<van-image lazy-load round fit="cover" width="65px" height="65px"
							:src="userInfo.avatar_url" />
					</div>
					<div style="display: flex;align-items: flex-start;flex-direction: column;padding-left: 10px;">
						<div
							style="color: orange;font-weight: bold;font-size: 18px;line-height:2px;margin-bottom: -5px;">
							<p>{{userInfo.nickname}}</p>
						</div>
						<p style="font-size:15px;line-height:5px;">
							<span style="color:gray;">关注</span>
							<span>&#8194;</span>
							<span style="font-size: 17px;font-weight: 550;">{{userInfo.following_count}}</span>
							<span>&#8195;</span>
							<span style="color:gray;">粉丝</span>
							<span>&#8194;</span>
							<span style="font-size: 17px;font-weight: 550;">{{userInfo.follower_count}}</span>
						</p>
					</div>
				</div>
			</template>
			<template #right-icon>
				<van-icon name="arrow" color="rgb(150,150,150)" />
			</template>
		</van-cell>
		<div style="height: 10px;"></div>
	</div>
</template>

<script>

const themeVars = {
	cellLineHeight: '150px',
	cellIconSize: '150px',
}

export default {
	name: 'FollowersFansCard',
	props: ['userInfo'],
	computed: {
		themeVars() {
			return themeVars
		},
	},
};
</script>

<style>
</style>