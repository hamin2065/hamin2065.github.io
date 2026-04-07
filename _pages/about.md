---
layout: about
title: About
permalink: /
subtitle:
nav: true
_styles: >
  div.post article div.clearfix a,
  div.post article div.clearfix p a,
  div.post article div.clearfix a:link,
  div.post article div.clearfix p a:link,
  div.post article div.clearfix a:visited,
  div.post article div.clearfix p a:visited {
    color: #000 !important;
  }
  div.post article div.clearfix a:hover,
  div.post article div.clearfix p a:hover {
    color: #000 !important;
    text-decoration: underline;
  }
  html[data-theme="dark"] div.post article div.clearfix a,
  html[data-theme="dark"] div.post article div.clearfix p a,
  html[data-theme="dark"] div.post article div.clearfix a:link,
  html[data-theme="dark"] div.post article div.clearfix p a:link,
  html[data-theme="dark"] div.post article div.clearfix a:visited,
  html[data-theme="dark"] div.post article div.clearfix p a:visited {
    color: #fff !important;
  }
  html[data-theme="dark"] div.post article div.clearfix a:hover,
  html[data-theme="dark"] div.post article div.clearfix p a:hover {
    color: #fff !important;
    text-decoration: underline;
  }
  .section-heading {
    color: #000 !important;
    border-bottom: 3px solid #023B74 !important;
  }
  .section-heading a {
    color: #000 !important;
  }
  .section-heading.publications-heading {
    border-bottom-width: 3px !important;
    margin-top: 2em !important;
  }
  html[data-theme="dark"] .section-heading {
    color: var(--global-text-color) !important;
    border-bottom-color: #79C9C5 !important;
  }
  html[data-theme="dark"] .section-heading a {
    color: var(--global-text-color) !important;
  }
  .profile {
    width: 20% !important;
  }
  @media (max-width: 575px) {
    .profile {
      width: 50% !important;
    }
  }

profile:
  align: right
  image: hamin_temp__.png
  image_circular: false # crops the image to make it circular
  more_info: >
    <p style="font-size: 1.5em; margin: 0.5em 0; display: flex; justify-content: space-between; width: 100%;">
      <a href="mailto:hamin2065@yonsei.ac.kr" style="text-decoration: none; color: inherit;" title="Email">
        <i class="fa-solid fa-envelope"></i>
      </a>
      <a href="https://github.com/hamin2065" target="_blank" rel="noopener noreferrer" style="text-decoration: none; color: inherit;" title="GitHub">
        <i class="fa-brands fa-github"></i>
      </a>
      <a href="https://scholar.google.com/citations?user=POt9uBgAAAAJ&hl=ko" target="_blank" rel="noopener noreferrer" style="text-decoration: none; color: inherit;" title="Google Scholar">
        <i class="fa-brands fa-google-scholar"></i>
      </a>
      <a href="https://www.linkedin.com/in/hamin-koo-66a440399" target="_blank" rel="noopener noreferrer" style="text-decoration: none; color: inherit;" title="LinkedIn">
        <i class="fa-brands fa-linkedin"></i>
      </a>
    </p>

selected_papers: true # includes a list of papers marked as "selected={true}"
social: false # includes social icons at the bottom of the page

announcements:
  enabled: true # includes a list of news items
  scrollable: true # adds a vertical scroll bar if there are more than 3 news items
  limit: 2 # leave blank to include all the news in the `_news` folder

latest_posts:
  enabled: false # set to false to hide the latest posts section
  scrollable: true # adds a vertical scroll bar if there are more than 3 new posts items
  limit: 3 # leave blank to include all the blog posts
---

Hello! I am a Master student in AI at Yonsei University, advised by Prof. [Jaehyung Kim](https://sites.google.com/view/jaehyungkim) in the [Machine and Language Learning Lab (ML3)](https://ml3.yonsei.ac.kr/).

I’m interested in understanding and controlling how large language models (LLMs) behave in practice. In particular, I study emergent behaviors such as systematic biases, robustness issues, and other unintended patterns. My work focuses on building structured and data-driven methods to analyze and improve the reliability of these models across different settings.