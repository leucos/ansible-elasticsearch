{% set unicast_hosts_allow = [] %}
{% if elasticsearch_cluster_name is defined %}
{%   for hst in groups[elasticsearch_cluster_name] %}
{%     set _ = unicast_hosts_allow.append(hostvars[hst]['ansible_' + elasticsearch_transport_interface].ipv4.address) %}
{%   endfor %}
{% endif %}

{% set client_hosts_allow = [] -%}
{%- for elt in elasticsearch_filter_allow_http_port %}
  {% if elt in hostvars %}
  {# this is a node #}
    {%- set _ = client_hosts_allow.extend(hostvars[elt]['ansible_' + elasticsearch_network_interface].ipv4.address) -%}
  {% elif elt|ipaddr %}
  {# this is an IP #}
    {%- set _ = client_hosts_allow.append(elt) -%}
  {% else %}
  {# this is a group #}
    {% for hst in groups[elt] %}
    {% endfor %}
  {% endif %}
{% endfor -%}
