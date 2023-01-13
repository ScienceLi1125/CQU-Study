import apiAxios from "./axios"
import { Toast } from "vant"

//所有文章
export async function getAllArticles(page) {
    const task = apiAxios({
        url: `posts/?page=${page}`,
        method: 'get',
    })
    try {
        const result = await task
        return result.data
    } catch (error) {
        if (!error.response.status) {
            Toast.fail("服务器没有响应或本地无网络连接")
        }
        else if (error.response.data === 500) {
            Toast.fail("服务器出现了一点问题")
        }
        else {
            Toast.fail(`获取所有文章失败${JSON.stringify(error.response.data)}`)
        }
    }
}

//文章评论
export async function getAllComments(article_id,page) {
    const task = apiAxios({
        url: `posts/${article_id}/comment/?page=${page}`,
        method: 'get',
    })
    try {
        const result = await task
        return result.data
    } catch (error) {
        if (!error.response.status) {
            Toast.fail("服务器没有响应或本地无网络连接")
        }
        else if (error.response.data === 500) {
            Toast.fail("服务器出现了一点问题")
        }
        else {
            Toast.fail(`获取文章评论失败${JSON.stringify(error.response.data)}`)
        }
    }
}

//文章详情
export async function getArticleDetail(article_id) {
    const task = apiAxios({
        url: `posts/${article_id}/`,
        method: 'get',
    })
    try {
        const result = await task
        return result.data
    } catch (error) {
        if (!error.response.status) {
            Toast.fail("服务器没有响应或本地无网络连接")
        }
        else if (error.response.data === 500) {
            Toast.fail("服务器出现了一点问题")
        }
        else {
            Toast.fail(`加载文章信息失败${JSON.stringify(error.response.data)}`)
        }
    }
}

//管理员文章删除或删除自己文章
export async function deleteArticle(article_id) {
    const task = apiAxios({
        url: `posts/${article_id}/`,
        method: 'delete',
    })
    try {
        const result = await task
        return result.data
    } catch (error) {
        if (!error.response.status) {
            Toast.fail("服务器没有响应或本地无网络连接")
        }
        else if (error.response.data === 500) {
            Toast.fail("服务器出现了一点问题")
        }
        else {
            Toast.fail(`删除文章失败${JSON.stringify(error.response.data)}`)
        }
    }
}

//仅用于文章详情页面,点赞后更新状态
export function getArticleLikedCount(article_id) {
    return apiAxios({
        url: `posts/${article_id}/liked_count/`,
        method: 'get',
    })
}

//仅用于文章详情页面,点赞后更新状态
export function getArticleCommentCount(article_id) {
    return apiAxios({
        url: `posts/${article_id}/comment_count/`,
        method: 'get',
    })
}

//发布文章界面上传文章图片
export function uploadArticleImage(image) {
    const formdata = new FormData()
    formdata.append("image",image)
    return apiAxios({
        url: `image/`,
        method: 'post',
        data: formdata,
        header: {
            'Content-Type' : 'multipart/form-data',
        },
    })
}

//发布文章
export function publishArticle(jsonBody) {
    return apiAxios({
        url: `posts/`,
        method: 'post',
        data: jsonBody,
    })
}

//发布评论
export function publishComment(article_id,comment) {
    return apiAxios({
        url: `posts/${article_id}/reply/`,
        method: 'post',
        data: {post:comment,
               title:"评论"},
    })
}

//点赞文章
export function likeArticle(article_id) {
    return apiAxios({
        url: `posts/${article_id}/like/`,
        method: 'post',
    })
}

//取消文章点赞
export function cancelLikeArticle(article_id) {
    return apiAxios({
        url: `posts/${article_id}/like/`,
        method: 'delete',
    })
}

//文章详情页面获取用户点赞状态
export function getIsLikedArticle(article_id) {
    return apiAxios({
        url: `posts/${article_id}/liked/`,
        method: 'get',
    })
}

//获取关注用户的文章
export async function getFollowedArticle(page) {
	const task = apiAxios({
			url: `posts/?page=${page}&only_see_following=true`,
			method: `get`,
	})
    try {
        const result = await task
        return result.data
    } catch (error) {
        if (!error.response.status) {
            Toast.fail("服务器没有响应或本地无网络连接")
        }
        else if (error.response.data === 500) {
            Toast.fail("服务器出现了一点问题")
        }
        else {
            Toast.fail(`获取关注用户文章失败${JSON.stringify(error.response.data)}`)
        }
    }
}

//拉取可用的讲话人,说话风格选项
export async function getVoiceOptions() {
	const task = apiAxios({
        url: `voice_options/`,
        method: `get`,
    })
    try {
        const result = await task
        return result.data
    } catch (error) {
        if (!error.response.status) {
            Toast.fail("服务器没有响应或本地无网络连接")
        }
        else if (error.response.data === 500) {
            Toast.fail("服务器出现了一点问题")
        }
        else {
            Toast.fail(`获取语音生成选项失败${JSON.stringify(error.response.data)}`)
        }
    }
}