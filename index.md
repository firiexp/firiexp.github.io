イ

{% assign mydocs = site.library | group_by: 'category' %}
{% for i in mydocs %}
## {{ i.name }}
    {% assign items = i.items | sort 'title' %}
    {% for item in items %}
* [{{item.title}}]({{ item.url | relative_url }})
    {% endfor %}
{% endfor %}