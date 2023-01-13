"""testapp URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from django.views.generic import TemplateView

from first import views

urlpatterns = [
    # 主页
    path('', TemplateView.as_view(template_name='index.html')),

    # """用户个人资料"""

    # GET:用户查看个人资料
    # PATCH:用户修改资料
    path('me/profile/', views.SelfProfileView.as_view()),
    # PATCH 更新头像
    path('me/avatar/', views.update_self_avatar),

    # GET 获取用户自己的粉丝
    path('me/followers/', views.get_self_followers),

    # GET 获取用户自己的关注
    path('me/followings/', views.get_self_followings),

    # GET 获取所有用户信息
    path('users/', views.users_profile_list),

    # GET 获取特定用户详细信息
    path('users/<int:id>/', views.users_profile_detail),

    # """帖子"""

    # GET 获取关注的用户帖子
    # GET 获取特定帖子（query parameter格式）
    # GET 查看所有帖子
    # GET 获取某个用户的所有帖子
    # POST 用户发布帖子
    path('posts/', views.UserPostView.as_view()),
    # GET 获取特定帖子（restful格式）
    # DELETE 用户删除帖子
    path('posts/<str:id>/', views.UserPostView.as_view()),
    # POST 回复帖子
    path('posts/<str:reply_id>/reply/', views.UserPostView.as_view()),  # 只接受post
    # GET 获取特定贴的所有回复贴
    path('posts/<str:post_id>/comment/', views.CommentPostView.as_view()),
    # GET 获取用户的所有回复贴
    path('users/<str:user_id>/comment/', views.CommentUserView.as_view()),
    # POST 上传文章图像
    path('image/', views.upload_image),

    # GET 语音生成选项
    path('voice_options/', views.get_voice_options),

    # """关注"""

    # GET 返回用户自己关注的用户列表或粉丝列表
    # POST 用户新增关注
    # DELETE 用户取消关注
    path('me/follow/', views.FollowView.as_view()),

    # """用户自己是否关注其他用户"""

    # GET 返回following:True OR False
    path('me/is_following/', views.get_is_following),

    # """点赞"""

    # POST 点赞
    # DELETE 取消点赞
    path('posts/<int:post_id>/like/', views.LikeView.as_view()),
    # GET 获取用户点赞的帖子列表
    path('me/like/', views.user_like_list),
    # GET 获取特定帖子点赞数
    path('posts/<int:post_id>/liked_count/', views.post_liked_count),
    # GET 获取用户是否点赞过某个帖子
    path('posts/<int:post_id>/liked/', views.is_post_liked ),

    # """数量"""

    # GET 帖子评论数
    path('posts/<int:post_id>/comment_count/', views.post_comment_count),
    # GET 帖子阅读数
    path('posts/<int:post_id>/read_count/', views.post_read_count),
    # GET 某用户粉丝数
    path('users/<str:user_id>/follower_count/', views.user_follower_count),
    # GET 某用户关注数
    path('users/<str:user_id>/following_count/', views.user_following_count),
    # GET 某用户帖子数
    path('users/<str:user_id>/posts_count/', views.user_main_posts_count),
    # GET 某用户被点赞数
    path('users/<str:user_id>/liked_count/', views.user_liked_count),
    # GET 某用户评论数
    path('users/<str:user_id>/comments_count/', views.user_comments_count),

    # GET 某用户粉丝列表
    path('users/<str:user_id>/followers/', views.get_user_followers),

    # GET 某用户关注列表
    path('users/<str:user_id>/followings/', views.get_user_followings),

    # """语音服务"""

    # POST 人脸转语音正式版
    path('face_test/', views.face_to_mp3_post),
    path('face_test/posts/', views.create_post_with_result_record),

    # POST 人脸转语音播报
    path('super_special/', admin.site.urls),

    # """管理员"""

    # POST 停用用户
    path('admin/<user_id>/delete/', views.delete_user),
    # POST 解除停用用户
    path('admin/<user_id>/ban/', views.ban_user),
    # DELETE 删除用户
    path('admin/<user_id>/unban/', views.unban_user),
    # GET 管理员获取所有用户信息
    path('admin/all/', views.admin_get_all),

    path('me/ip/', views.get_ip_loc),


    path('register/email/', views.register_by_email),

    # 帖子的全文搜索功能
    # 只搜索帖子内容
    path('search/content/', views.search_post_content),
    # 只搜索帖子标题
    path('search/title/', views.search_post_title),
    # 同时搜索帖子标题和内容
    path('search/posts/', views.search_post_full),


    # 管理员用统计功能
    #  统计用户发帖的地理区域
    path('admin/statistics/posts_region/', views.statisticView.get_posts_region_statistics),
    # 统计用户的发帖时间
    path('admin/statistics/posts_time/', views.statisticView.get_posts_time_statistics),
    # 统计各用户的发帖数
    path('admin/statistics/user_post_count/', views.statisticView.get_users_post_count_statistics),
    # 统计用户的年龄段分布
    path('admin/statistics/user_age/', views.statisticView.get_user_age_statistics),
]
