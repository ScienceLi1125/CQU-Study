import apiAxios from "./axios"
import { Toast } from "vant"

//获取给定ID的用户个人信息
export async function getUserProfile(id) {
    const task = apiAxios({
        url: `users/${id}/`,
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
            Toast.fail(`加载用户信息失败${JSON.stringify(error.response.data)}`)
        }
    }
    return null
}

//获取给定ID用户的粉丝
export async function getUserFollowers(user_id,page) {
    const task = apiAxios({
        url: `users/${user_id}/followers/?page=${page}`,
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
            Toast.fail(`加载用户粉丝列表失败${JSON.stringify(error.response.data)}`)
        }
    }
}

//获取给定ID用户的关注
export async function getUserFollowings(user_id,page) {
    const task = apiAxios({
        url: `users/${user_id}/followings/?page=${page}`,
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
            Toast.fail(`加载用户关注列表失败${JSON.stringify(error.response.data)}`)
        }
    }
}

//获取给定ID用户的文章列表
export async function getUserArticles(user_id,page) {
    const task = apiAxios({
        url: `posts/?user_id=${user_id}&page=${page}`,
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
            Toast.fail(`加载用户文章列表失败${JSON.stringify(error.response.data)}`)
        }
    }
}

//获取给定ID用户的评论列表
export async function getUserComments(user_id,page) {
    const task = apiAxios({
        url: `users/${user_id}/comment/?page=${page}`,
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
            Toast.fail(`加载用户评论列表失败${JSON.stringify(error.response.data)}`)
        }
    }
}