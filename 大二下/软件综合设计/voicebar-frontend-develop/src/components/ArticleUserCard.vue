<template>
    <van-cell center :value="floor_num" class="header-cell" :border="!disableBorder">
        <template #title>
			<div v-if="enableGap" style="height:5px"></div>
            <div @click.stop="onClickHead" class="title-container">
                <div class="title-avatar-container">
                    <div class="title-avatar-inner-container">
                        <van-image
                        lazy-load
                        round
                        fit="cover"
                        :src="avatar_url"
                        width="50"
                        height="50"
                        />
                    </div>
                </div>
                <div class="title-info-container">
                    <div class="title-info-name-container" :style="{color: nickname_color}">{{nickname}}</div>
					<div style="display: flex;">
						<div class="title-info-time-container">{{publish_time}}</div>
						<div style="width: 10px;"></div>
						<div class="title-info-ip-container"> {{ip_loc}}</div>
					</div>
                </div>
            </div>
            <div v-if="enableGap" style="height:10px"></div>
        </template>
    </van-cell>
</template>

<script>

export default {
    name: 'ArticleUserCard',
    props: ['user_id','avatar_url','nickname','publish_time','enableGap','disableBorder', 'ip_loc', 'floor_num', 'is_admin'],
    emits: ['clickHead'],
    methods: {
        onClickHead() {
            this.$emit('clickHead',this.user_id)
        }
    },
	computed: {
		nickname_color() {
			if(this.is_admin) {
				return '#0DC160'
			}
			else {
				return '#FFBF65'
			}
		}
	}
}

</script>

<style lang="scss" scoped>

.title-container {
    display: flex;
    .title-avatar-container {
        display: flex;
        justify-content: center;
        width: 60px;
        left: 0;
        .title-avatar-inner-container {
            display: flex;
            justify-content: center;
            flex-direction: column;
        }
    }
    .title-info-container {
        padding-left: 5px;
        .title-info-name-container {
            padding-top: 5px;
            font-weight: bold;
            font-size: medium;
        }
        .title-info-time-container {
            color: gray;
            font-size: small;
        }
		.title-info-ip-container {
			color: gray;
			font-size: small;
		}
    }
}

.header-cell {
    padding-bottom: 0px;
    padding-top: 0px;
    :deep(.van-cell__title) {
        min-width: 80%;
        text-align: left;
    }
}

</style>