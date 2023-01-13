from rest_framework import serializers
from .models import User,UserPost,Follow,Like,UserImage,UserVoice,UserAITest

class UserProfileSerializer(serializers.ModelSerializer):

    def validate_nickname(self,value):
        '''
        禁止空名
        '''
        if value == '':
            raise serializers.ValidationError("禁止空名")
        return value

    def validate_age(self,value):
        '''
        禁止超级长寿
        '''
        if value >= 150:
            raise serializers.ValidationError("禁止超级长寿")
        return value

    class Meta:
        model = User
        fields = ['id','gender','age','motto','nickname','avatar_url','is_admin', 'is_banned']
        read_only_fields = ('id','avatar_url','is_admin')


class UserProfileListSerializer(serializers.ModelSerializer):
    '''
    列出数据库中用户
    '''
    class Meta:
        model = User
        fields = ['id','gender','age','nickname','avatar_url',]
        read_only_fields = ('id','gender','age','nickname','avatar_url',)



class UserPostSerializer(serializers.ModelSerializer):
    '''
    用户发布帖子
    '''
    class Meta:
        model = UserPost
        fields = ['id', 'user', 'post', 'pub_date', 'reply_to', 'visited_count', 'title', 'ip_loc']


class FollowSerializer(serializers.ModelSerializer):
    '''
    用户关注其他用户
    '''
    class Meta:
        model = Follow
        fields = ['id','user','follower']

class LikeSerializer(serializers.ModelSerializer):
    '''
    用户点赞帖子
    '''
    class Meta:
        model = Like
        fields = ['id','user','post']

class UpdateAvatarSerializer(serializers.Serializer):
    '''
    解析更新头像的请求
    '''
    avatar = serializers.ImageField(allow_empty_file=False)

class UploadPostImageSerializer(serializers.Serializer):
    '''
    解析上传文章图像,上传人脸识别图像的请求
    '''
    image = serializers.ImageField(allow_empty_file=False)

class CreatePostImageSerializer(serializers.Serializer):
    '''
    反序列化并验证创建帖子使用的图片
    '''
    #在serializer中使用user
    #https://stackoverflow.com/questions/27934822/get-current-user-in-model-serializer
    images = serializers.ListField(
             child=serializers.IntegerField(min_value=1),
             min_length=0,
             max_length=9,
             required=True,
             )

    # Create a custom method field
    current_user = serializers.SerializerMethodField('_user')

    # Use this method for the custom field
    def _user(self):
        request = self.context.get('request', None)
        if request:
            return request.user
    
    def validate_images(self, value):
        """
        1.图像必须存在
        2.图像未绑定帖子
        3.用户是图像的创建者
        """
        for image_id in value:
            try:
                image = UserImage.objects.get(id=image_id)
                if image.post_id:
                    raise serializers.ValidationError("图像已经被帖子使用了")
                user = self._user()
                if user.id != image.creator_id:
                    raise serializers.ValidationError("图像不属于你")
            except UserImage.DoesNotExist:
                raise serializers.ValidationError("图像不存在")
        return value

class CreatePostEnableReadSerializer(serializers.Serializer):
    '''
    反序列化是否启用语音朗读
    '''
    enableVoice = serializers.BooleanField(required=True)

class CreatePostReadOptionSerializer(serializers.Serializer):
    '''
    反序列化语音朗读的选项
    '''
    speakerId = serializers.IntegerField(min_value=0,required=True)
    styleId = serializers.IntegerField(min_value=0,required=True)

class GetPostImageSerializer(serializers.ModelSerializer):
    class Meta:
        model = UserImage
        fields = ['image_url']

class GetPostSerializer(serializers.ModelSerializer):
    '''
    序列化获取帖子信息
    '''
    #https://stackoverflow.com/questions/45987763/serializer-nested-relationships-not-working-as-it-sholuld-be
    #自动获取外键绑定对象
    images = GetPostImageSerializer(
                    many=True,
                    read_only=True,
                )
    voice_url = serializers.SlugRelatedField(
        read_only=True,
        source='voice',
        slug_field='voice_url'
     )

    class Meta:
        model = UserPost
        fields = ['id', 'user', 'post', 'pub_date', 'reply_to', 'visited_count', 'title', 'images', 'ip_loc', 'voice_url']


class UserSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = ['authingid', 'gender', 'age', 'motto', 'nickname', 'avatar_url', 'is_admin', 'is_banned']


class GetIsFollowingSerializer(serializers.Serializer):
    user_id = serializers.IntegerField(min_value=1,required=True)

class UserFollowersCountField(serializers.Field):
    """
    序列化用户的粉丝数
    """
    def to_representation(self, value:User):
        return Follow.objects.filter(user=value.id).count()

    def get_attribute(self, instance):
        return instance

class UserFollowingsCountField(serializers.Field):
    """
    序列化用户的关注数
    """
    def to_representation(self, value:User):
        return Follow.objects.filter(follower=value.id).count()

    def get_attribute(self, instance):
        return instance

class GetUserFollowSerializer(serializers.ModelSerializer):

    follower_count = UserFollowersCountField()
    following_count = UserFollowingsCountField()

    class Meta:
        model = User
        fields = ['id','gender', 'age', 'motto', 'nickname', 'avatar_url', 'is_admin', 'is_banned', 'follower_count', 'following_count']
        read_only_fields = ('id','gender', 'age', 'motto', 'nickname', 'avatar_url', 'is_admin', 'is_banned', 'follower_count', 'following_count')

class GetParamsPageSerializer(serializers.Serializer):
    page = serializers.IntegerField(min_value=1,required=True)

class CreatePostFaceResultSerializer(serializers.Serializer):
    '''
    反序列化使用人脸识别记录发布帖子的参数
    '''
    #在serializer中使用user
    #https://stackoverflow.com/questions/27934822/get-current-user-in-model-serializer
    result_id = serializers.IntegerField(min_value=1,required=True)
    title = serializers.CharField(allow_blank=False,max_length=100)

    # Use this method for the custom field
    def _user(self):
        request = self.context.get('request', None)
        if request:
            return request.user
    
    def validate_result_id(self, value):
        """
        1.记录必须存在
        3.用户是记录的创建者
        """
        try:
            result = UserAITest.objects.get(id=value)
            user = self._user()
            if user.id != result.creator_id:
                raise serializers.ValidationError("记录不属于你")
        except UserAITest.DoesNotExist:
            raise serializers.ValidationError("记录不存在")
        return value