import apiAxios from "./axios"
import FormData from 'form-data'
import { Toast } from "vant"

//性别枚举常量
const Gender = {
    NA:1,
    MALE:2,
    FEMALE:3,
    NON_BINARY:4
}
Object.freeze(Gender)
export {Gender}

//获取用户自己的个人信息
export function getSelfProfile() {
    return apiAxios({
        url: 'me/profile/',
        method: 'get',
    })
}

//更新用户自己的个人信息
export function updateSelfProfile(profile) {
    return apiAxios({
        url: 'me/profile/',
        method: 'patch',
        data: profile,
    })
}

//上传新头像
export function updateAvatar(new_avatar) {
    const formdata = new FormData()
    formdata.append("avatar",new_avatar,'new_avatar.png')
    return apiAxios({
        url: 'me/avatar/',
        method: 'patch',
        data: formdata,
        header: {
            'Content-Type' : 'multipart/form-data',
        },
    })
}

//获得已登录用户对某个用户的关注状态
export async function getIsFollowingUser(user_id) {
    const task = apiAxios({
        url: `me/is_following/?user_id=${user_id}`,
        method: 'get',
    })
    try {
        const result = await task
        return result.data.following
    } catch (error) {
        if (!error.response.status) {
            Toast.fail("服务器没有响应或本地无网络连接")
        }
        else if (error.response.data === 500) {
            Toast.fail("服务器出现了一点问题")
        }
        else {
            Toast.fail(`加载用户关注状态失败${JSON.stringify(error.response.data)}`)
        }
    }
}

//关注用户
export async function followUser(user_id) {
    const task = apiAxios({
        url: `me/follow/`,
        method: 'post',
        data: {user:user_id},
    })
    try {
        await task
    } catch (error) {
        if (!error.response.status) {
            Toast.fail("服务器没有响应或本地无网络连接")
        }
        else if (error.response.data === 500) {
            Toast.fail("服务器出现了一点问题")
        }
        else {
            Toast.fail(`关注用户失败${JSON.stringify(error.response.data)}`)
        }
    }
}

//取消关注用户
export async function cancelFollowUser(user_id) {
    const task = apiAxios({
        url: `me/follow/?user=${user_id}`,
        method: 'delete',
    })
    try {
        await task
    } catch (error) {
        if (!error.response.status) {
            Toast.fail("服务器没有响应或本地无网络连接")
        }
        else if (error.response.data === 500) {
            Toast.fail("服务器出现了一点问题")
        }
        else {
            Toast.fail(`取消关注用户失败${JSON.stringify(error.response.data)}`)
        }
    }
}

//获取用户自己的关注列表
export async function getSelfFollowings(page) {
    const task = apiAxios({
        url: `me/followings/?page=${page}`,
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
            Toast.fail(`加载关注列表失败${JSON.stringify(error.response.data)}`)
        }
    }
}

//获取用户自己的粉丝列表
export async function getSelfFollowers(page) {
    const task = apiAxios({
        url: `me/followers/?page=${page}`,
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
            Toast.fail(`加载粉丝列表失败${JSON.stringify(error.response.data)}`)
        }
    }
}