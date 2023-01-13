//存放使用localStorage缓存的函数

//用户个人信息部分
export function storeUserProfile(userProfile) {
    localStorage.userprofile = JSON.stringify(userProfile)
}

export function retrieveUserProfile() {
    if (localStorage.userprofile) {
    return JSON.parse(localStorage.userprofile)
    }
}

export function removeUserProfile() {
    localStorage.removeItem('userprofile')
}

//语音生成——说话人ID
export function storeVoiceSpeaker(speaker_index) {
    localStorage.voicespeaker = speaker_index
}

export function retrieveVoiceSpeaker() {
    if (localStorage.voicespeaker) {
    return JSON.parse(localStorage.voicespeaker)
    }
}

export function removeVoiceSpeaker() {
    localStorage.removeItem('voicespeaker')
}

//语音生成——说话风格ID
export function storeVoiceSpeakerStyle(style_index) {
    localStorage.voicespeakerstyle = style_index
}

export function retrieveVoiceSpeakerStyle() {
    if (localStorage.voicespeakerstyle) {
        return JSON.parse(localStorage.voicespeakerstyle)
    }
}

export function removeVoiceSpeakerStyle() {
    localStorage.removeItem('voicespeakerstyle')
}

//语音生成——可用选项
export function storeVoiceOptions(Options) {
    localStorage.voiceoptions = JSON.stringify(Options)
}

export function retrieveVoiceOptions() {
    if (localStorage.voiceoptions) {
        return JSON.parse(localStorage.voiceoptions)
    }
}

export function removeVoiceOptions() {
    localStorage.removeItem('voiceoptions')
}

//语音生成——启用语音朗读
export function storeEnableVoice(enable) {
    if (enable) {localStorage.enablevoice = '1'}
    else {localStorage.enablevoice = '0'}
}

export function retrieveEnableVoice() {
    if (localStorage.enablevoice) {
        if (localStorage.enablevoice === '1') {
            return true
        }
        return false
    }
}

export function removeEnableVoice() {
    localStorage.removeItem('enablevoice')
}