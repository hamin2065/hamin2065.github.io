source "https://rubygems.org"

# Ruby 2.7: needed for jekyll-scholar/bibtex-ruby (Ruby 3.x breaks with "Proc without block").
ruby "~> 2.7.0"

# Pin deps that default to Ruby 3+ when using Ruby 2.7
gem "ffi", "~> 1.15.0"       # 1.17+ requires Ruby 3.0+
gem "nokogiri", "~> 1.15.0"  # 1.16.2+ requires Ruby 3.1+

# GitHub Pages: 227 allows nokogiri 1.15.x (Ruby 2.7). 232+ requires nokogiri 1.16+ (Ruby 3.1+).
gem "github-pages", "227", group: :jekyll_plugins

# al-folio 전용 플러그인 (github-pages에 없는 것들)
group :jekyll_plugins do
  gem "jekyll-3rd-party-libraries"
  gem "jekyll-archives-v2"
  gem "jekyll-cache-bust"
  gem "jekyll-email-protect"
  gem "jekyll-get-json"
  gem "jekyll-link-attributes"
  gem "jekyll-minifier"
  gem "jekyll-paginate-v2"
  gem "jekyll-regex-replace"
  gem "jekyll-scholar"
  gem "jekyll-socials"
  gem "jekyll-tabs"
  gem "jekyll-terser", git: "https://github.com/RobertoJBeltran/jekyll-terser.git"
  gem "jekyll-toc"
  gem "jemoji"
  gem "classifier-reborn"
end

group :other_plugins do
  gem "css_parser"
  gem "feedjira"
  gem "httparty"
  gem "observer"
end

# Ruby 2.7 default gem compatibility on GitHub Actions.
gem "uri", "0.10.0.2"
