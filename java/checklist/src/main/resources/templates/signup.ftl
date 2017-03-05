<#import "layout.ftl" as layout>
<@layout.myLayout>
<div class="page-header text-center">
    <h3> Sign Up </h3>
</div>

<div class="panel-body" ng-app="myApp" ng-controller="myController">

    <form class="form-horizontal" ng-submit="submitForm()">
        <div class="form-group">
            <label for="title" class="col-md-4 control-label">Username</label>
            <div class="col-md-8">
                <input type="text" class="form-control" id="username" placeholder="Username" ng-model="user.username">
                <span ng-show="errorName">{{errorUserName}}</span>
            </div>
        </div>

        <div class="form-group">
            <label for="title" class="col-md-4 control-label">Email</label>
            <div class="col-md-8">
                <input type="email" class="form-control" id="email" placeholder="email" ng-model="user.email">
                <span ng-show="errorName">{{errorEmail}}</span>
            </div>
        </div>

        <div class="form-group">
            <label for="title" class="col-md-4 control-label">Password</label>
            <div class="col-md-8">
                <input type="password" class="form-control" id="password" placeholder="Password" ng-model="user.password">
                <span ng-show="errorName">{{errorPassword}}</span>
            </div>
        </div>

        <div class="form-group">
            <label for="title" class="col-md-4 control-label">Password Confirmation</label>
            <div class="col-md-8">
                <input type="password" class="form-control" id="passwordConfirmation" placeholder="Password" ng-model="user.passwordConfirmation">
                <span ng-show="errorName">{{errorPasswordConfirmation}}</span>
            </div>
        </div>


        <div class="form-group">
            <div class="col-md-10"></div>
            <div class="col-md-2">
                <input class="btn btn-success btn-lg" type="submit" value="submit">
            </div>
        </div>
    </form>
</div> <!-- panel-body end -->

<script>
    $('li:eq(2)').addClass('active');
</script>
</@layout.myLayout>





