import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../views/HomeView.vue'
import LoginView from '../views/LoginView.vue'
import SettingView from '../views/SettingView.vue'
import ProfileSettingView from '../views/ProfileSettingView.vue'
import NewArticleView from '../views/NewArticle.vue'
import MeView from '../views/MeView.vue'
import AItestView from '../views/AItest.vue'
import MyComment from '../views/MyComment.vue'
import MyArticle from '../views/MyArticle.vue'
import PhototoVoiceView from '../views/PhototoVoiceView.vue'
import UserInfoView from '../views/UserInfoView.vue'
import OthersArticle from '../views/OthersArticle.vue'
import OthersComment from '../views/OthersComment.vue'
import FollowingsView from '../views/FollowingsView.vue'
import FollowersView from '../views/FollowersView.vue'
import ArticleView from '../views/ArticleView.vue'
import OthersProfile from '../views/OthersProfile.vue'
import FollowView from '../views/FollowView.vue'

const routes = [
  {
    path: '/user/:user_id/follower',
    name: 'othersfollowers',
    component: FollowersView,
    alias: ['/:user_id/follower'], //用于复用页面  因我的粉丝与ta的粉丝只有导航栏有差异
    meta: {
      requiresAuth: true,
      transition: 'van-slide-left',
    }
  },
  {
    path: '/user/:user_id/following',
    name: 'othersfollowings',
    component: FollowingsView,
    alias: ['/:user_id/following'], //用于复用页面  因我的关注与ta的关注只有导航栏有差异
    meta: {
      requiresAuth: true,
      transition: 'van-slide-left',
    }
  },
  {
    path: '/user/:user_id/comment',
    name: 'otherscomment',
    component: OthersComment,
    meta: {
      requiresAuth: true,
      transition: 'van-slide-left',
    }
  },
  {
    path: '/user/:user_id/article',
    name: 'othersarticle',
    component: OthersArticle,
    meta: {
      requiresAuth: true,
      transition: 'van-slide-left',
    }
  },
  {
    path: '/me/comment',
    name: 'mycomment',
    component: MyComment,
    meta: {
      requiresAuth: true,
      transition: 'van-slide-left',
    }
  },
  {
    path: '/',
    name: 'home',
    component: HomeView,
    meta: {
      requiresAuth: true,
      transition: 'van-slide-left',
    }
  },
  {
	path: '/followview',
	name: 'followview',
	component: FollowView,
	meta: {
		requiresAuth: true,
    transition: 'van-slide-left',
	}
  },
  {
    path: '/me',
    name: 'me',
    component: MeView,
    meta: {
      requiresAuth: true,
      transition: 'van-slide-left',
    }
  },
  {
    path: '/login',
    name: 'login',
    component: LoginView,
  },
  {
    path: '/me/setting',
    name: 'setting',
    component: SettingView,
    meta: {
      requiresAuth: true,
      transition: 'van-slide-left',
    }
  },
  {
    path: '/me/profile',
    name: 'profile',
    component: ProfileSettingView,
    meta: {
      requiresAuth: true,
      transition: 'van-slide-left',
    }
  },
  {
    path: '/newarticle',
    name: 'newarticle',
    component: NewArticleView,
    meta: {
      requiresAuth: true,
      transition: 'van-fade',
    }
  },
  {
    path: '/me/article',
    name: 'myarticle',
    component: MyArticle,
    meta: {
      requiresAuth: true,
      transition: 'van-slide-left',
    }
  },
  {
    path: '/phototovoice',
    name: 'phototovoice',
    component: PhototoVoiceView,
    meta: {
      requiresAuth: true,
      transition: 'van-slide-left',
    }
  },
  {
    path: '/phototovoice/aitest',
    name: 'aitest',
    component: AItestView,
    meta: {
      requiresAuth: true,
      transition: 'van-slide-left',
    }
  },
  {
	path: '/user/:user_id',
	name: 'userinfoview',
	component: UserInfoView,
	meta: {
		requiresAuth: true,
    transition: 'van-slide-left',
	}
  },
  {
    path: '/article/:article_id',
    name: 'article_detail',
    component: ArticleView,
    meta: {
      requiresAuth: true,
      transition: 'van-slide-left',
    }
  },
  {
    path: '/user/:user_id/profile',
    name: 'othersprofile',
    component: OthersProfile,
    meta: {
      requiresAuth: true,
      transition: 'van-slide-left',
    }
  },
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
})

router.beforeEach((to, from, next) => {
  if (to.name === 'login' && localStorage._authing_token) {
    //前往登录页但是已经登陆
    next({ path: '/' })
  } else {
    next() // 其余
  }
})

//https://stackoverflow.com/questions/52653337/vuejs-redirect-from-login-register-to-home-if-already-loggedin-redirect-from
//全局路由守卫,若未登陆则要求登陆
router.beforeEach((to, from, next) => {
  if (to.matched.some(record => record.meta.requiresAuth)) {
    // this route requires auth, check if logged in
    // if not, redirect to login page.
    if (!localStorage._authing_token) { //使用localStorage中的内容判断,store中的内容在刷新时会短暂消失
      next({ name: 'login' })
    } else {
      next() // go to wherever I'm going
    }
  } else {
    next() // does not require auth, make sure to always call next()!
  }
})

export default router
