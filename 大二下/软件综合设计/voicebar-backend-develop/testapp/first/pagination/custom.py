class CustomPagination:

    PAGE_SIZE = 10

    @classmethod
    def paginate_queryset(cls, page_number, queryset):
        start_offset = (page_number-1) * cls.PAGE_SIZE
        return queryset[start_offset:start_offset+cls.PAGE_SIZE]