<template>
	<!-- 动画 -->
  <router-view v-slot="{ Component, route }">
    <transition :name="route.meta.transition">
      <div style="height:0px;" :key="route.path">
        <component :is="Component"/>
      </div>
    </transition>
  </router-view>
  

  <van-tabbar v-if="showTabBar" fixed route :border="false">
    <van-tabbar-item replace to="/" icon="wap-home-o">所有文章</van-tabbar-item>
    <van-tabbar-item replace to="/followview" icon="eye-o">关注</van-tabbar-item>
    <van-tabbar-item to="/newarticle">
      <div class="tabbar-add-container">
        <div class="tabbar-add-wrap">
          <van-icon name="add" color="rgb(250, 194, 9)" size="55" />
        </div>
      </div>
    </van-tabbar-item>
    <van-tabbar-item replace to="/phototovoice" icon="photo-o">照片语音</van-tabbar-item>
    <van-tabbar-item replace to="/me" icon="manager-o">我的</van-tabbar-item>
  </van-tabbar>
</template>


<script>
import "@authing/vue-ui-components/lib/index.min.css";
// Default theme. ~960B
import '@vime/core/themes/default.css';

// Optional light theme (extends default). ~400B
import '@vime/core/themes/light.css';

const tabbarBlacklist = ['/login','/me/setting','/newarticle','/me/following','/me/follower','/me/profile','/me/article','/me/comment', '/phototovoice/aitest', '/otherview/othersprofile', /^\/article\/[0-9]+$/, /^\/user\/[0-9]+$/, /^\/user\/[0-9]+\/profile$/,/^\/user\/[0-9]+\/following$/,/^\/user\/[0-9]+\/follower$/,/^\/user\/[0-9]+\/article$/,/^\/user\/[0-9]+\/comment$/] //把不需要底部导航栏的页面路径放在这个数组里面

export default {
  name:'App',
  computed: {
    tabbarBlacklist () { //暴露常量,在哪些页面不显示底边栏？
      return tabbarBlacklist
    },
    showTabBar() { //是否显示底边导航栏
      const currentPath = this.$route.path
      return !this.tabbarBlacklist.some(
        (blackListRoute) => {
          return currentPath === blackListRoute || (blackListRoute instanceof RegExp && currentPath.match(blackListRoute))
        }
      )
    }
  },
}

</script>

<style lang="scss">
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #323233;
  background-color: #f7f8fa;
  margin-top: 0px;
}

.tabbar-add-container {
  width: 60px;
  height: 60px;
  .tabbar-add-wrap {
    max-width: 100%;
  }
}
</style>

