from django.db import models
from django.db.models import UniqueConstraint


# Create your models here.


class User(models.Model):
    objects = models.Manager()

    class Gender(models.IntegerChoices):
        NA = 1, "不适用"
        MALE = 2, "男"
        FEMALE = 3, "女"
        NON_BINARY = 4, "非二元"

    authingid = models.CharField(max_length=100, unique=True)
    gender = models.PositiveSmallIntegerField(
        choices=Gender.choices,
        default=Gender.NA
    )
    age = models.PositiveSmallIntegerField(default=1)
    motto = models.CharField(max_length=200)
    nickname = models.CharField(max_length=16, default="新用户")

    avatar_url = models.URLField(
        default="https://voicebar-1251996605.cos.ap-shanghai.myqcloud.com/avatar/default_avatar.png")

    follower = models.ManyToManyField(
        'self',
        through='Follow',
        through_fields=('user', 'follower'),
    )

    likes = models.ManyToManyField(
        'UserPost',
        through='Like',
        through_fields=('user', 'post'),
        related_name='likes',
    )

    is_admin = models.BooleanField(default=False)
    is_banned = models.BooleanField(default=False)


from django.utils import timezone


class UserPost(models.Model):
    objects = models.Manager()
    user = models.ForeignKey(User, on_delete=models.CASCADE, default=1)
    post = models.CharField(max_length=512)
    pub_date = models.DateTimeField(default=timezone.now)

    reply_to = models.ForeignKey("self", on_delete=models.CASCADE, null=True, blank=True)
    visited_count = models.PositiveSmallIntegerField(default=0)
    title = models.CharField(max_length=100,default="标题")

    ip_loc = models.CharField(max_length=50,default="未知")  # 帖子发布的地址
    def __str__(self) -> str:
        return self.post.__str__()


class Follow(models.Model):
    objects = models.Manager()
    user = models.ForeignKey(User, on_delete=models.CASCADE, related_name='following+')  # 被关注者
    follower = models.ForeignKey(User, on_delete=models.CASCADE, related_name='follower+', default=7)  # 关注者

    def __str__(self) -> str:
        return self.follower.__str__() + " follows " + self.user.__str__()

    class Meta:
        constraints = [UniqueConstraint(fields=['user', 'follower'], name='unique_follow')]


class Like(models.Model):
    objects = models.Manager()
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    post = models.ForeignKey(UserPost, on_delete=models.CASCADE)

    def __str__(self) -> str:
        return self.user.__str__() + " likes " + self.post.__str__()

    class Meta:
        constraints = [UniqueConstraint(fields=['user', 'post'], name='unique_like')]

class UserImage(models.Model):
    objects = models.Manager()
    creator = models.ForeignKey(User, on_delete=models.CASCADE)
    image_url = models.URLField(null=False)
    post = models.ForeignKey(UserPost, on_delete=models.CASCADE, null=True, related_name='images')

class UserVoice(models.Model):
    objects = models.Manager()
    creator = models.ForeignKey(User, on_delete=models.CASCADE)
    voice_url = models.URLField(null=False)
    post = models.OneToOneField(UserPost, on_delete=models.CASCADE, null=False, related_name='voice')

class UserAITest(models.Model):
    objects = models.Manager()
    creator = models.ForeignKey(User, on_delete=models.CASCADE)
    json_result = models.JSONField(null=False)
    voice_url = models.URLField(null=False)
    image_url = models.URLField(null=False,default="https://voicebar-1251996605.cos.ap-shanghai.myqcloud.com/avatar/default_avatar.png")