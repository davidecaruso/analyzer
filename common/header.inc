<nav>
    <div class="navbar-fixed nav-wrapper <?= $_color ?> <?= $_brightness != '' ? $_brightness . $_intensity : null ?>">
        <a href="javascript:;" class="brand-logo link-title center">Analyzer</a>
        <a href="javascript:;" data-activates="mobile-nav" class="button-collapse"><i class="material-icons">menu</i></a>
        <? if ($logged) { ?>
            <ul class="right hide-on-med-and-down">
                <!--<li>-->
                <!--    <a href="javascript:;"><i class="material-icons">search</i></a>-->
                <!--</li>-->
                <!--<li>-->
                <!--    <a href="javascript:;"><i class="material-icons">view_module</i></a>-->
                <!--</li>-->
                <li>
                    <a href="?logout" class="waves-effect waves-light"><i class="material-icons" title="Logout">eject</i></a>
                </li>
                <!--<li>-->
                <!--    <a href="mobile.html" class="dropdown-button" data-activates="dropdown1"><i class="material-icons right">more_vert</i></a>-->
                <!--    <ul id="dropdown1" class="dropdown-content">-->
                <!--        <li><a href="javascript:;" class="waves-effect waves---><?//= $_color ?><!--">ITEM 1</a></li>-->
                <!--        <li><a href="javascript:;" class="waves-effect waves---><?//= $_color ?><!--">ITEM 2</a></li>-->
                <!--        <li class="divider"></li>-->
                <!--        <li><a href="javascript:;" class="waves-effect waves---><?//= $_color ?><!--">ITEM 3</a></li>-->
                <!--    </ul>-->
                <!--</li>-->
            </ul>
        <? } ?>
        <ul class="side-nav" id="mobile-nav">
            <li id="logo-container">
                <a href="javascript:;" class="brand-logo">
                    <img src="logo.png" width="200" height="200" align="top" alt="Analyzer" title="Analyzer" />
                </a>
            </li>
            <? if ($logged) { ?>
                <li><a href="?logout" class="waves-effect waves-<?= $_color ?>">Logout</a></li>
            <? } else { ?>
                <li><a href="<?= $authUrl ?>" class="waves-effect waves-<?= $_color ?>">Login</a></li>
            <? } ?>
            <!--<li><a href="javascript:;" class="waves-effect waves---><?//= $_color ?><!--">ITEM 3</a></li>-->
            <!--<li class="no-padding">-->
            <!--    <ul class="collapsible collapsible-accordion">-->
            <!--        <li class="bold"><a class="collapsible-header waves-effect waves---><?//= $_color ?><!--">DROPDOWN</a>-->
            <!--            <div class="collapsible-body">-->
            <!--                <ul>-->
            <!--                    <li><a href="javascript:;" class="waves-effect waves---><?//= $_color ?><!--">ITEM 1</a></li>-->
            <!--                    <li><a href="javascript:;" class="waves-effect waves---><?//= $_color ?><!--">ITEM 2</a></li>-->
            <!--                    <li class="divider"></li>-->
            <!--                    <li><a href="javascript:;" class="waves-effect waves---><?//= $_color ?><!--">ITEM 3</a></li>-->
            <!--                </ul>-->
            <!--            </div>-->
            <!--        </li>-->
            <!--    </ul>-->
            <!--</li>-->
        </ul>
    </div>
</nav>